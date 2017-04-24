from Parser import Parser
from Global import Global
from EntityMother import EntityMother
from Main import Main
from Makefile import Makefile

import sys

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
