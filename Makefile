
all:
	(cd cmd && make)
	(cd pashkowsky-hw01 && make)
	(cd plugins/car_control && make)

clean:
	(cd cmd && make clean)
	(cd pashkowsky-hw01 && make clean)
	(cd plugins/car_control && make clean)

.PHONY: all clean
