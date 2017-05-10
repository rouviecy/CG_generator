from Parser import Parser
from Global import Global
from EntityMother import EntityMother
from Main import Main
from Makefile import Makefile

import sys, os

if __name__ == '__main__':
	workspaceName = sys.argv[1]
	workspace = '../Workspace/' + workspaceName + '/'
	parser = Parser(workspace)
	parser.analyse()
	makefile = Makefile(workspace)
	makefile.write(parser.entities)
	main = Main(workspace)
	main.write(parser.entities)
	parser.globalBloc.write(parser.entities)
	parser.game.write(parser.globalBloc, parser.entities)
	entityMother = EntityMother(workspace)
	entityMother.write(parser.entities)
	for entity in parser.entities:
		entity.write()
	mono = open(workspace + '/monolithe.cpp', 'w')
	mono.write(parser.globalBloc.genExcludedIncludes())
	mono.close()
	os.system('cd ' + workspace + 'bin; cmake ../readonly/; make cg; make cgcode; cd ..;cat bin/CMakeFiles/cgcode.dir/mainMono_readonly.cpp.o >> ./monolithe.cpp;')
	
