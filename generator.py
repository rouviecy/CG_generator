from Parser import Parser
from Writer import Writer

import sys

if __name__ == '__main__':
	parser = Parser(sys.argv[1])
	writer = Writer(sys.argv[2])
	parser.analyse()
	writer.generate(parser)
