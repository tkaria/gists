import zmq
import proto_objs.spot_fx_md_1_pb2

# Create context and connect
context = zmq.Context()
fxcm = context.socket(zmq.SUB)
xcde = context.socket(zmq.SUB)

# Use below for direct market subscription

fxcm.connect("tcp://127.0.0.1:5273")
xcde.connect("tcp://127.0.0.1:5271")
# Use below for aggregated book
#socket.connect("tcp://83.160.107.178:9000")

fxcm.setsockopt(zmq.SUBSCRIBE, "")
xcde.setsockopt(zmq.SUBSCRIBE, "")
# Use below for direct market subscription
#fxcm.setsockopt(zmq.SUBSCRIBE, "EUR/USD")

while True:
    # N.B. only aggregated book has topc and contents
    # while direct market data sends only protobuf
    #[topic, contents] = socket.recv_multipart()
    poller = zmq.Poller()
    poller.register(fxcm, zmq.POLLIN)
    poller.register(xcde, zmq.POLLIN)
    while True:
        socks = dict(poller.poll())

        if fxcm in socks and socks[fxcm] == zmq.POLLIN:
            message = fxcm.recv()
            bbo = proto_objs.spot_fx_md_1_pb2.instrument_bbo();
            bbo.ParseFromString(message);
            print "FXCM: ", bbo.symbol, bbo.bb_venue_id, bbo.bb_price, bbo.bb_size, "@", bbo.ba_venue_id, bbo.ba_price, bbo.ba_size

        if xcde in socks and socks[xcde] == zmq.POLLIN:
            message = xcde.recv()
            bbo = proto_objs.spot_fx_md_1_pb2.instrument_bbo();
            bbo.ParseFromString(message);
            print "XCDE: ", bbo.symbol, bbo.bb_venue_id, bbo.bb_price, bbo.bb_size, "@", bbo.ba_venue_id, bbo.ba_price, bbo.ba_size

