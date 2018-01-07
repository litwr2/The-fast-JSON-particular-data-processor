CXXFLAGS = -O3 -s
#CXXFLAGS = -g
LOGDIR = log

ALL = generate-log-files serv-list2 serv-map2

ALL: $(ALL)

generate-log-files: generate-log-files.cpp Makefile
	g++ -pthread $(CXXFLAGS) -o $@ $<

serv-list2: serv-list2.cpp Makefile
	g++ -pthread $(CXXFLAGS) -o $@ $<

serv-map2: serv-map2.cpp Makefile
	g++ -pthread $(CXXFLAGS) -o $@ $<

test:
	@rm -rf $(LOGDIR)
	@mkdir $(LOGDIR)
	./generate-log-files
	./serv-list2
	@mv agr.txt agr2.txt
	./serv-map2
	@diff agr2.txt agr.txt
	sort -r -k 13 agr.txt >agr-sorted.txt
	@rm agr2.txt
	@echo Test passed

clean:
	rm -rf $(ALL) $(LOGDIR) agr*.txt
