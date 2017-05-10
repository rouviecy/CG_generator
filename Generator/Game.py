from Indentable import Indentable
from Extractor import Extractor

class Game(Indentable):
	
	def __init__(self, workspace):
		self.workspace = workspace
		self.argumentsGame = []
		self.argumentsTurn = []
		self.variables = []
		self.argumentNbEntities = None
		self.nbEntityArgs = 0

	def decode(self, bloc):
		self.argumentsGame = Extractor.extractList('argsGame', bloc)
		self.argumentsTurn = Extractor.extractList('argsTurn', bloc)
		self.variables = Extractor.extractList('vars', bloc)
		self.argumentNbEntities = Extractor.extractParam('argumentNbEntities', bloc)
		self.nbEntityArgs = int(Extractor.extractParam('nbEntityArgs', bloc))

	def write(self, globalBloc, entities):
		readonlyH = open(self.workspace + "readonly/Game_readonly.h", 'w')
		readonlyCPP = open(self.workspace + "readonly/Game_readonly.cpp", 'w')
		templateH = open(self.workspace + "template/Game.h", 'w')
		templateCPP = open(self.workspace + "template/Game.cpp", 'w')
		readonlyH.write(self.genReadonlyH(entities))
		readonlyCPP.write(self.genReadonlyCPP(globalBloc, entities))
		templateH.write(self.genTemplateH())
		templateCPP.write(self.genTemplateCPP())
		readonlyH.close()
		readonlyCPP.close()
		templateH.close()
		templateCPP.close()

	def genReadonlyH(self, entities):
		text = "#ifndef GAME_READONLY_H\n"
		text += "#define GAME_READONLY_H\n\n"
		for entity in entities:
			text += "#include \"../custom/entities/" + entity.name + ".h\"\n"
		text += "\n"
		text += "class Game_readonly{\n"
		text += self.indent(1) + "public:\n"
		for argument in self.argumentsGame:
			text += self.indent(2) + "int " + argument + ";\n"
		for variable in self.variables:
			text += self.indent(2) + "int " + argument + ";\n"
		for entity in entities:
			text += self.indent(2) + "map <int, " + entity.name + "> " + entity.dico + ";\n"
		text += self.indent(2) + "Game_readonly();\n"
		text += self.indent(2) + "void InputTurn();\n"
		text += self.indent(2) + "void Action();\n"
		text += self.indent(1) + "private:\n"
		text += self.indent(2) + "template <class EntityType> void DeleteObsoleteEntities(map <int, EntityType> *dicoToClean, map <int, bool> *dicoStillExists);\n"
		text += self.indent(2) + "template <class EntityType> void RefreshDico(map <int, EntityType> *dicoToClean, map <int, bool> *dicoStillExists, int id);\n"
		text += "};\n\n"
		text += "#endif"
		return text

	def genReadonlyCPP(self, globalBloc, entities):
		text = "#include \"Game_readonly.h\"\n"
		text += "\n"
		text += "Game_readonly::Game_readonly(){\n"
		if len(self.argumentsGame) > 0:
			text += self.indent(1) + "cin "
			for argument in self.argumentsGame:
				text += ">> " + argument + " "
			text += "; cin.ignore();\n"
		for variable in self.variables:
			text += self.indent(1) + "this->" + variable + " = 0;\n"
		text += "}\n\n"
		text += "void Game_readonly::InputTurn(){\n"
		if len(entities) > 0:
			text += self.indent(1) + "map <int, bool> "
			first = True
			for entity in entities:
				if not first:
					text += ", "
				text += entity.dico + "StillExists"
				first = False
			text += ";\n"
		if len(self.argumentsTurn) > 0:
			text += self.indent(1) + "int "
			first = True
			for argument in self.argumentsTurn:
				if not first:
					text += ", "
				text += argument
				first = False
			text += ";\n"
		if len(self.argumentsTurn) > 0:
			text += self.indent(1) + "cin"
			for argument in self.argumentsTurn:
				text += " >> " + argument
			text += "; cin.ignore();\n"
		text += self.indent(1) + "for(int i = 0; i < " + str(self.nbEntityArgs) + "; i++){\n"
		text += self.indent(2) + "int id, x, y"
		for i in range(self.nbEntityArgs):
			text += ", arg" + str(i + 1)
		text += ";\n"
		text += self.indent(2) + "string entityType;\n"
		text += self.indent(2) + "cin >> id >> entityType >> x >> y"
		for i in range(self.nbEntityArgs):
			text += " >> arg" + str(i + 1)
		text += "; cin.ignore();\n"
		text += self.indent(2) + "if(false){}\n"
		for entity in entities:
			text += self.indent(2) + "else if(entityType.compare(\"" + entity.entity + "\") == 0){\n"
			text += self.indent(3) + entity.dico + "[id].Update(id, x, y"
			i = 0
			for argument in entity.arguments:
				text += ", arg" + str(i + 1)
				i += 1
			text += ");\n"
			text += self.indent(3) + "RefreshDico<" + entity.name + ">(&" + entity.dico + ", &" + entity.dico + "StillExists, id);\n"
			text += self.indent(2) + "}\n"
		text += self.indent(1) + "}\n"
		for entity in entities:
			text += self.indent(1) + "DeleteObsoleteEntities<" + entity.name + ">(&" + entity.dico + ", &" + entity.dico + "StillExists);\n"
		text += "}\n\n"
		text += "void Game_readonly::Action(){\n"
		text += self.indent(1) + "// Inserer ici les operations utiles pour chaque tour\n"
		text += "}\n\n"
		text += "template <class EntityType> void Game_readonly::DeleteObsoleteEntities(map <int, EntityType> *dicoToClean, map <int, bool> *dicoStillExists){\n"
		if globalBloc.magicMap:
			text += self.indent(1) + "forMapTypename(int, EntityType, it, (*dicoToClean)){\n"
		else:
			text += self.indent(1) + "for(typename map <int, Entity> ::iterator it = dicoToClean->begin(); it != dicoToClean->end(); ++it){\n"
		text += self.indent(2) + "if(dicoStillExists->find(it->first) == dicoStillExists->end()){it = dicoToClean->erase(it);}\n"
		text += self.indent(2) + "else{++it;}\n"
		text += self.indent(1) + "}\n"
		text += "}\n\n"
		text += "template <class EntityType> void Game_readonly::RefreshDico(map <int, EntityType> *dicoToRefresh, map <int, bool> *dicoStillExists, int id){\n"
		text += self.indent(1) + "if(dicoToRefresh->find(id) == dicoToRefresh->end()){(*dicoToRefresh)[id] = EntityType();}\n"
		text += self.indent(1) + "(*dicoStillExists)[id] = true;\n"
		text += "}"
		return text

	def genTemplateH(self):
		text = "#ifndef GAME_H\n"
		text += "#define GAME_H\n\n"
		text += "#include \"../readonly/Game_readonly.h\"\n\n"
		text += "class Game : public Game_readonly{\n"
		text += self.indent(1) + "public:\n"
		text += self.indent(2) + "Game();\n"
		text += self.indent(2) + "void InputTurn();\n"
		text += self.indent(2) + "void Action();\n"
		text += self.indent(1) + "private:\n"
		text += "};\n\n"
		text += "#endif"
		return text

	def genTemplateCPP(self):
		text = "#include \"Game.h\"\n\n"
		text += "Game::Game() : Game_readonly(){\n\n"
		text += "}\n\n"
		text += "void Game::InputTurn(){\n"
		text += self.indent(1) + "Game_readonly::InputTurn();\n\n"
		text += "}\n\n"
		text += "void Game::Action(){\n"
		text += self.indent(1) + "Game_readonly::Action();\n\n"
		text += "}"
		return text
