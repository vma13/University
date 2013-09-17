THREADS = threads
WCDOG = watchdog
OPTIONS = -Wall -o3 -pipe -lm
LIBS = -pthread

defaulte:  cleane compile run

cleane:
	rm -rf $(THREADS) $(WCDOG)

compile: $(THREADS).c $(WCDOG).c
	gcc $(OPTIONS) $(LIBS) $(THREADS).c -o $(THREADS)
	gcc $(OPTIONS) $(WCDOG).c -o $(WCDOG)

run:
	./watchdog
		

