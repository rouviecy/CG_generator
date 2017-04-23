from Global import Global
from Entity import Entity

class Writer:
	
	def __init__(self, outputPath):
		self.outputPath = outputPath

	def generate(self, parser):
		globalBloc = parser.globalBloc
		game = parser.game
		entities = parser.entities
		fichier = open(self.outputPath, 'w')
		output = ""
		output += self.genGlobalBloc(globalBloc)
		output += self.genListClasses(entities)
		output += self.genGameH(entities)
		output += self.genEntityMotherH()
		for entity in entities:
			output += self.genEntityChildH(entity)
		output += self.genEntityMotherCPP()
		for entity in entities:
			output += self.genEntityChildCPP(entity)
		output += self.genGameCPP(globalBloc, game, entities)
		output += self.genMain()
		fichier.write(output)
		fichier.close()

	def genGlobalBloc(self, globalBloc):
		text = ""
		for include in globalBloc.includes:
			text += "#include <" + include + ">\n"
		text += "\n"
		for namespace in globalBloc.namespaces:
			text += "using namespace " + namespace + ";\n"
		text += "\n"
		if globalBloc.magicMap:
			text += "#define forMap(type1, type2, it, carte) for(map<type1,type2>::iterator it = carte.begin(); it != carte.end(); ++it)\n\n"
		for defineKey in globalBloc.defines.keys():
			text += "#define " + defineKey + " " + str(globalBloc.defines[defineKey]) + "\n"
		text += "\n"
		return text

	def genListClasses(self, entities):
		text = "class Game;\nclass Entity;\n"
		for entity in entities:
			text += "class " + entity.name + ";\n"
		text += "\n"
		return text

	def genGameH(self, entities):
		text = "class Game{\n"
		text += self.indent(1) + "public:\n"
		for entity in entities:
			text += self.indent(2) + "map <int, " + entity.name + "> " + entity.dico + ";\n"
		text += self.indent(2) + "Game();\n"
		text += self.indent(2) + "void InputTurn();\n"
		text += self.indent(2) + "void Action();\n"
		text += self.indent(1) + "private:\n"
		text += self.indent(2) + "void DeleteObsoleteEntities(map <int, Entity> *dicoToClean, map <int, bool> *dicoStillExists);\n"
		text += self.indent(2) + "template <class EntityType> void RefreshDico(map <int, EntityType> *dicoToClean, map <int, bool> *dicoStillExists, int id);\n"
		text += "};\n\n"
		return text

	def genEntityMotherH(self):
		text = "class Entity{\n"
		text += self.indent(1) + "public:\n"
		text += self.indent(2) + "int id;\n"
		text += self.indent(2) + "int x;\n"
		text += self.indent(2) + "int y;\n"
		text += self.indent(2) + "Entity();\n"
		text += self.indent(2) + "Entity(int id, int x, int y);\n"
		text += self.indent(2) + "void Update(int id, int x, int y);\n"
		text += "};\n\n"
		return text

	def genGameCPP(self, globalBloc, game, entities):
		text = "Game::Game(){\n"
		if len(game.argumentsGame) > 0:
			text += self.indent(1) + "cin "
			for argument in game.argumentsGame:
				text += ">> " + argument + " "
			text += "; cin.ignore;\n"
		for variable in game.variables:
			text += self.indent(1) + "this->" + variable + " = 0;\n"
		text += "}\n\n"
		text += "void Game::InputTurn(){\n"
		if len(entities) > 0:
			text += self.indent(1) + "map <int, bool> "
			first = True
			for entity in entities:
				if not first:
					text += ", "
				text += entity.dico + "StillExists"
				first = False
			text += ";\n"
		if len(game.argumentsTurn) > 0:
			text += self.indent(1) + "cin"
			for argument in game.argumentsTurn:
				text += " >> " + argument
			text += "; cin.ignore;\n"
		text += self.indent(1) + "for(int i = 0; i < " + str(game.nbEntityArgs) + "; i++){\n"
		text += self.indent(2) + "int id, x, y"
		for i in range(game.nbEntityArgs):
			text += ", arg" + str(i + 1)
		text += ";\n"
		text += self.indent(2) + "string entityType;\n"
		text += self.indent(2) + "cin >> id >> entityType >> x >> y"
		for i in range(game.nbEntityArgs):
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
			text += self.indent(1) + "DeleteObsoleteEntities(&" + entity.dico + ", &" + entity.dico + "StillExists);\n"
		text += "}\n\n"
		text += "void Game::Action(){\n"
		text += self.indent(1) + "// Inserer ici les operations utiles pour chaque tour\n"
		text += "}\n\n"
		text += "void Game::DeleteObsoleteEntities(map <int, Entity> *dicoToClean, map <int, bool> *dicoStillExists){\n"
		if globalBloc.magicMap:
			text += self.indent(1) + "forMap(int, Entity, it, (*dicoToClean)){\n"
		else:
			text += self.indent(1) + "for(map <int, Entity> ::iterator it = dicoToClean->begin(); it != dicoToClean->end(); ++it){\n"
		text += self.indent(2) + "if(dicoStillExists->find(it->first) == dicoStillExists->end()){it = dicoToClean->erase(it);}\n"
		text += self.indent(2) + "else{++it;}\n"
		text += self.indent(1) + "}\n"
		text += "}\n\n"
		text += "template <class EntityType> void Game::RefreshDico(map <int, EntityType> *dicoToRefresh, map <int, bool> *dicoStillExists, int id){\n"
		text += self.indent(1) + "if(dicoToRefresh->find(id) == dicoToRefresh->end()){(*dicoToRefresh)[id] = EntityType();}\n"
		text += self.indent(1) + "(*dicoStillExists)[id] = true;\n"
		text += "}\n\n"
		return text
		
	def genEntityMotherCPP(self):
		text = "Entity::Entity() : Entity(-1, 0, 0){}\n\n"
		text += "Entity::Entity(int id, int x, int y){\n"
		text += self.indent(1) + "Entity::Update(id, x, y);\n"
		text += "}\n\n"
		text += "void Entity::Update(int id, int x, int y){\n"
		text += self.indent(1) + "this->id = id;\n"
		text += self.indent(1) + "this->x = x;\n"
		text += self.indent(1) + "this->y = y;\n"
		text += "}\n\n"
		return text

	def genEntityChildH(self, entity):
		text = "class " + entity.name + " : public Entity{\n"
		text += self.indent(1) + "public:\n"
		for argument in entity.arguments:
			text += self.indent(2) + "int " + argument + ";\n"
		for variable in entity.variables:
			text += self.indent(2) + "int " + variable + ";\n"
		text += self.indent(2) + entity.name + "();\n"
		text += self.indent(2) + "void Update(int id, int x, int y"
		for argument in entity.arguments:
			text += ", int " + argument
		text += ");\n"
		text += "};\n\n"
		return text

	def genEntityChildCPP(self, entity):
		text = entity.name + "::" + entity.name + "() : Entity(){\n"
		for variable in entity.variables:
			text += self.indent(1) + "this->" + variable + " = 0;\n"
		text += "}\n\n"
		text += "void " + entity.name + "::Update(int id, int x, int y"
		for argument in entity.arguments:
			text += ", int " + argument
		text += "){\n"
		text += self.indent(1) + "Entity::Update(id, x, y);\n"
		for argument in entity.arguments:
			text += self.indent(1) + "this->" + argument + " = " + argument + ";\n"
		text += "}\n\n"
		return text

	def genMain(self):
		text = "int main(){\n"
		text += self.indent(1) + "Game game;\n"
		text += self.indent(1) + "while(1){\n"
		text += self.indent(2) + "game.InputTurn();\n"
		text += self.indent(2) + "game.Action();\n"
		text += self.indent(1) + "}\n"
		text += "}\n\n"
		return text

	def indent(self, nb):
		indentItem = "    "
		text = ""
		for i in range(nb):
			text += indentItem
		return text
