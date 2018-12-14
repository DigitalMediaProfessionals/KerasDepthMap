include ../../env.mk

INC = -I../../dv-user-driver/include -I../common/include -I/usr/include/agg2 `freetype-config --cflags`
LIB = -L../../dv-user-driver -ldmpdv -L../common/lib -ldv700_util -lagg -lfreetype $(shell pkg-config --cflags --libs opencv)

CXXFLAGS = -pthread -std=c++11 $(OPT) -Wall -Werror -c $(INC)
LDFLAGS = -pthread $(LIB)

DEPS = KerasDepthMap_gen.h imagenet_1000_categories.h
OBJS = KerasDepthMap_gen.o 
TGT  = bin/KerasDepthMap bin/KerasDepthMap_threaded

all : $(TGT)

%.o: %.cpp $(DEPS)
	$(GPP) $(CXXFLAGS) -o $@ $<

bin/KerasDepthMap: $(OBJS) depthMap.o
	$(CXX) -o $@ $^ $(LDFLAGS)

bin/KerasDepthMap_threaded: $(OBJS) depthMap_threaded.o
	$(CXX) -o $@ $^ $(LDFLAGS)


clean:
	rm *.o
	rm -f $(TGT)

