include ../../env.mk

INC = -I../common/include -I/usr/include/agg2 `freetype-config --cflags`
LIB = -ldmpdv -L../common/lib -ldv700_util -lagg -lfreetype $(shell pkg-config --cflags --libs opencv)

CFLAGS = -pthread -std=c++11 $(OPT) -Wall -Werror -c $(INC)
LFLAGS = -pthread $(LIB)

DEPS = KerasDepthMap_gen.h imagenet_1000_categories.h
OBJS = KerasDepthMap_gen.o 
TGT  = bin/KerasDepthMap bin/KerasDepthMap_pipelined

all : $(TGT)

%.o: %.cpp $(DEPS)
	$(GPP) $(CFLAGS) -o $@ $<

bin/KerasDepthMap: $(OBJS) depthMap.o
	$(GPP) -o $@ $^ $(LFLAGS)

bin/KerasDepthMap_pipelined: $(OBJS) depthMap_pipelined.o
	$(GPP) -o $@ $^ $(LFLAGS)


clean:
	rm *.o
	rm -f $(TGT)

