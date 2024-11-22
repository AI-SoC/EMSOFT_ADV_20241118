all :
	gcc -g -o main *.c
	./main

clean :
	rm main *.out callgrind.out.* cachegrind.out.* massif.out.*

valgrind :
	valgrind --leak-check=yes ./main

callgrind :
	valgrind --tool=callgrind ./main
	callgrind_annotate callgrind.out.*

callgrind_gui :
	kcachegrind callgrind.out.*

cachegrind :
	valgrind --tool=cachegrind --log-file=cachegrind.out ./main
	cg_annotate cachegrind.out.*

cachegrind_gui :
	kcachegrind cachegrind.out.*

massif :
	valgrind --tool=massif --time-unit=B --massif-out-file=massif.out ./main
	ms_print massif.out

massif_gui :
	massif-visualizer massif.out
