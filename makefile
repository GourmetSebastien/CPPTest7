.SILENT:
	
CLASSES=Classes/
OBJS=$(CLASSES)Modele.o $(CLASSES)Voiture.o $(CLASSES)Option.o $(CLASSES)Exception.o $(CLASSES)OptionException.o
CO=g++ -I $(CLASSES) -D DEBUG
PROGRAMS=Test7


Test7:	Test7.cpp Modele.o Voiture.o Option.o Exception.o OptionException.o
	$(CO) Test7.cpp $(OBJS) -o Test7
	echo "Creation de Test7"

Modele.o:	$(CLASSES)Modele.h $(CLASSES)Modele.cpp
	$(CO) $(CLASSES)Modele.cpp -c -o $(CLASSES)Modele.o
	echo "Creation de Modele.o"

Voiture.o:	$(CLASSES)Voiture.h $(CLASSES)Voiture.cpp
	$(CO) $(CLASSES)Voiture.cpp -c -o $(CLASSES)Voiture.o
	echo "Creation de Voiture.o"

Option.o:	$(CLASSES)Option.h $(CLASSES)Option.cpp
	$(CO) $(CLASSES)Option.cpp -c -o $(CLASSES)Option.o
	echo "Creation de Option.o"

Exception.o:	$(CLASSES)Exception.h $(CLASSES)Exception.cpp
	$(CO) $(CLASSES)Exception.cpp -c -o $(CLASSES)Exception.o
	echo "Creation de Exception.o"

OptionException.o:	$(CLASSES)OptionException.h $(CLASSES)OptionException.cpp
	$(CO) $(CLASSES)OptionException.cpp -c -o $(CLASSES)OptionException.o
	echo "Creation de OptionException.o"

clobber:	clean
	
	rm -f $(PROGRAMS)
	rm *.opt
	rm *.mod
	rm *.car

clean:	
	rm $(CLASSES)*.o
