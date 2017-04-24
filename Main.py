from Indentable import Indentable

class Main(Indentable):

	def __init__(self):
		pass

	def write(self, entities):
		readonlyCPP = open("./CPP/readonly/main.cpp", 'w')
		readonlyCPP.write(self.genReadonlyCPP(entities))

	def genReadonlyCPP(self, entities):
		text = "#include \"../custom/Game.h\"\n"
		text += "\n"
		text += "int main(){\n"
		text += self.indent(1) + "Game game;\n"
		text += self.indent(1) + "while(1){\n"
		text += self.indent(2) + "game.InputTurn();\n"
		text += self.indent(2) + "game.Action();\n"
		text += self.indent(1) + "}\n"
		text += "}"
		return text
