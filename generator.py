from Parser import Parser
from Global import Global
from EntityMother import EntityMother
from Main import Main
from Makefile import Makefile

import sys, os

if __name__ == '__main__':
	parser = Parser(sys.argv[1])
	parser.analyse()
	makefile = Makefile()
	makefile.write(parser.entities)
	main = Main()
	main.write(parser.entities)
	parser.globalBloc.write(parser.entities)
	parser.game.write(parser.globalBloc, parser.entities)
	entityMother = EntityMother()
	entityMother.write(parser.entities)
	for entity in parser.entities:
		entity.write()
	mono = open('generatedMono.cpp', 'w')
	mono.write(parser.globalBloc.genExcludedIncludes())
	mono.close()
	os.system("cd bin; cmake ..; make cg; make cgcode; cd ..; cat bin/CMakeFiles/cgcode.dir/CPP/readonly/mainMono.cpp.o >> ./generatedMono.cpp;")
	
