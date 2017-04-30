from Indentable import Indentable

class Main(Indentable):

	def __init__(self):
		pass

	def write(self, entities):
		readonlyCPP = open("./CPP/readonly/main.cpp", 'w')
		readonlyCPP.write(self.genReadonlyCPP(entities))
		readonlyMonoCPP = open("./CPP/readonly/mainMono.cpp", 'w')
		readonlyMonoCPP.write(self.genReadonlyMonoCPP(entities))

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

	def genReadonlyMonoCPP(self, entities):
		text = "#include \"../custom/Game.cpp\"\n"
		text += "#include \"Game_readonly.cpp\"\n"
		text += "#include \"../custom/Entity.cpp\"\n"
		text += "#include \"Entity_readonly.cpp\"\n"
		for entity in entities:
			text += "#include \"../custom/entities/" + entity.name + ".cpp\"\n"
			text += "#include \"entities/" + entity.nameRE + ".cpp\"\n"
		text += "\n"
		text += self.genReadonlyCPP(entities)
		return text
