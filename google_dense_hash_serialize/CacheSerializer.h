#include "KMsgCache.h"
#include <google/dense_hash_map>

namespace std {
	template <>
	bool operator==(const std::pair<const strategy_id_t, route_t>& p1, 
				const std::pair<const strategy_id_t, route_t>& p2) 
	{
		std::cerr << "bool operator==(const std::pair<const strategy_id_t, route_t>)" << std::endl;
		return (p1.first == p2.first && p1.second == p2.second);
	};
	
	template <>
	bool operator==(const std::pair<const order_id_t, OrderInfo_ptr>& p1, 
				const std::pair<const order_id_t, OrderInfo_ptr>& p2) 
	{
		std::cout << "bool operator==(const std::pair<order_id_t, OrderInfo_ptr>)" << std::endl;
		return (p1.first == p2.first);// && p1.second == p2.second);
	};

};

struct StrategyCacheSerializer {
	bool operator()(FILE* fp, const std::pair<const strategy_id_t, route_t>& value) const {
		// Write the key
		if (fwrite(&value.first._sid, sizeof(value.first._sid), 1, fp) != 1) {
			return false;
		}
	
		// Write the size of the route table - number of entries
		if (fwrite(&value.second.num_nodes, sizeof(value.second.num_nodes), 1, fp) != 1) {
			return false;
		}
	
		// Write the route table
		if (fwrite(&value.second.nodes, sizeof(value.second.nodes), 1, fp) != 1) {
			return false;
		}
	
		return true;
	};

	bool operator()(FILE* fp, std::pair<const strategy_id_t, route_t>* value) const {
	// Read the key.  Note the need for const_cast to get around
	// the fact hash_map keys are always const.
	// Read the sid
		if (fread(const_cast<uuid_t*>(&value->first._sid), sizeof(value->first._sid), 1, fp) != 1) {
			return false;
		}

		// Read the number of nodes in route.
		if (fread(&value->second.num_nodes, sizeof(value->second.num_nodes), 1, fp) != 1) {
			return false;
		}

		// Read the route
		if (fread(&value->second.nodes, sizeof(value->second.nodes), 1, fp) != 1) {
			return false;
		}

		return true;
	};
};

struct OrderCacheSerializer {
	bool operator()(FILE* fp, const std::pair<const order_id_t, OrderInfo_ptr>& value) const {

		// Write the key
		if (fwrite(&value.first._oid, sizeof(value.first._oid), 1, fp) != 1) {
			return false;
		}

		if (value.second == OrderInfo_ptr()) {
			std::cerr << "SOMETHING IS ROTTEN HERE" << std::endl;
		}
		// Write the order id
		const order_id_t& oid = value.second->getOrderID();
		if (fwrite(&oid._oid, sizeof(oid._oid), 1, fp) != 1) {
			return false;
		}

		// Write the strategy id
		const strategy_id_t& sid = value.second->getStrategyID();
		if (fwrite(&sid._sid, sizeof(sid._sid), 1, fp) != 1) {
			return false;
		}

		// Write the status
		const OrderStatus_t& status = value.second->getStatus();
		if (fwrite(&status, sizeof(status), 1, fp) != 1) {
			return false;
		}
	
		return true;
	};

	bool operator()(FILE* fp, std::pair<const order_id_t, OrderInfo_ptr>* value) const {
		if (fread(const_cast<uuid_t*>(&(value->first._oid)), sizeof(value->first._oid), 1, fp) != 1) {
			return false;	
		}

		value->second = boost::make_shared<OrderInfo>();
		order_id_t oid;
		if (fread(&oid._oid, sizeof(oid._oid), 1, fp) != 1) {
			return false;
		}
		value->second->setOrderID(oid);

		strategy_id_t sid;
		if (fread(&sid._sid, sizeof(sid._sid), 1, fp) != 1) {
			return false;
		}
		value->second->setStrategyID(sid);

		OrderStatus_t status;
		if (fread(&status, sizeof(status), 1, fp) != 1) {
			return false;
		}
		value->second->setStatus(status);

		return true;
	};
};



