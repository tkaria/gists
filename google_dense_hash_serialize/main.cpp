#include <iostream>
#include <google/dense_hash_map>
#include <string>

using google::dense_hash_map;      // namespace where class lives by default
using std::cout;
using std::endl;
using std::tr1::hash;  // or __gnu_cxx::hash, or maybe tr1::hash, depending on your OS
using std::string;

struct StringToIntSerializer {
  bool operator()(FILE* fp, const std::pair<const int, std::string>& value) const {
    // Write the key.  We ignore endianness for this example.
    if (fwrite(&value.first, sizeof(value.first), 1, fp) != 1)
      return false;
    // Write the value.
    assert(value.second.length() <= 255);   // we only support writing small strings
    const unsigned char size = value.second.length();
    if (fwrite(&size, 1, 1, fp) != 1)
      return false;
    if (fwrite(value.second.data(), size, 1, fp) != 1)
      return false;
    return true;
  }

  bool operator()(FILE* fp, std::pair<const int, std::string>* value) const {
    // Read the key.  Note the need for const_cast to get around
    // the fact hash_map keys are always const.
    if (fread(const_cast<int*>(&value->first), sizeof(value->first), 1, fp) != 1)
      return false;
    // Read the value.
    unsigned char size;    // all strings are <= 255 chars long
    if (fread(&size, 1, 1, fp) != 1)
      return false;
    char* buf = new char[size];
    if (fread(buf, size, 1, fp) != 1) {
      delete[] buf;
      return false;
    }
    value->second.assign(buf, size);
    delete[] buf;
    return true;
  }
};

// Specialized template hash function for order_id_t and strategy_id_t
namespace std {
    namespace tr1 {
        template<> class hash< const int>
        {
            public:
                size_t operator() (const int& x) const {
                    //size_t hval = hashlittle(x._oid, UUID_LEN, 0);
                    return x;
                    //return hval;
                }
        };

    };
};

struct eq
{
	bool operator() (const int& l, const int& r) const {
		return l == r;
	}
};

typedef dense_hash_map<const int, std::string, std::tr1::hash<const int>,  eq> TESTMAP;

TESTMAP
CreateMap()
{
	//dense_hash_map<const int, std::string, std::tr1::hash<const int>, eq> map;
	TESTMAP map;
	map.set_empty_key(0);
	map[1] = "a";
	map[2] = "b";
	map[3] = "c";
	map[4] = "d";
	map[5] = "e";
	map[6] = "f";
	return map;
}

int
main()
{
	TESTMAP mymap = CreateMap();
	const int zero = 0;
	//mymap.set_empty_key(zero);
	//mymap.set_deleted_key(255);
	FILE* fp = fopen("hashtable.data", "w");
	mymap.serialize(StringToIntSerializer(), fp);
	fclose(fp);

	TESTMAP mymap2;
	mymap2.set_empty_key(zero);
	//mymap2.set_deleted_key(255);
	FILE* fp_in = fopen("hashtable.data", "r");
	mymap2.unserialize(StringToIntSerializer(), fp_in);
	fclose(fp_in);
	assert(mymap == mymap2);

	TESTMAP::iterator it = mymap2.begin();
	while (it != mymap2.end()) {
		std::cout << it->first << " = " << it->second << std::endl; 
		it++;
	}

	return 0;
}
