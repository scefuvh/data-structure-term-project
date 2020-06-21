.PHONY: source
source: task1 task2
	@echo "Begin compiling"

task1: ./task1.cpp ./include/name_index.h ./include/binary_search_tree.h ./source/name_index.cpp ./source/binary_search_tree.cpp
	g++ task1.cpp ./source/name_index.cpp -o task1
	chmod u+x task1

task2: ./task2.cpp ./include/style_class.h ./include/binary_search_tree.h ./source/style_class.cpp ./source/binary_search_tree.cpp
	g++ task2.cpp ./source/style_class.cpp -o task2
	chmod u+x task2

.PHONY: clean
clean:
	rm task1 task2 || true

.PHONY: remove
remove:
	rm ./*
