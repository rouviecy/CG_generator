from Indentable import Indentable
from Extractor import Extractor

class Entity(Indentable):
	
	def __init__(self, entity):
		self.entity = entity
		self.name = None
		self.nameRE = None
		self.dico = None
		self.arguments = []
		self.variables = []

	def decode(self, bloc):
		self.name = Extractor.extractParam('name', bloc)
		self.dico = Extractor.extractParam('dico', bloc)
		self.arguments = Extractor.extractList('args', bloc)
		self.variables = Extractor.extractList('vars', bloc)
		self.nameRE = self.name + "_readonly"

	def write(self):
		readonlyH = open("./CPP/readonly/entities/" + self.nameRE + ".h", 'w')
		readonlyCPP = open("./CPP/readonly/entities/" + self.nameRE + ".cpp", 'w')
		templateH = open("./CPP/template/entities/" + self.name + ".h", 'w')
		templateCPP = open("./CPP/template/entities/" + self.name + ".cpp", 'w')
		readonlyH.write(self.genReadonlyH())
		readonlyCPP.write(self.genReadonlyCPP())
		templateH.write(self.genTemplateH())
		templateCPP.write(self.genTemplateCPP())
		readonlyH.close()
		readonlyCPP.close()
		templateH.close()
		templateCPP.close()
		
	def genReadonlyH(self):
		text = "#ifndef " + self.name.upper() + "_READONLY_H\n"
		text += "#define " + self.name.upper() + "_READONLY_H\n\n"
		text += "#include \"../../custom/Entity.h\"\n"
		text += "\n"
		text += "class " + self.nameRE + " : public Entity{\n"
		text += self.indent(1) + "public:\n"
		for argument in self.arguments:
			text += self.indent(2) + "int " + argument + ";\n"
		for variable in self.variables:
			text += self.indent(2) + "int " + variable + ";\n"
		text += self.indent(2) + self.nameRE + "();\n"
		text += self.indent(2) + "void Update(int id, int x, int y"
		for argument in self.arguments:
			text += ", int " + argument
		text += ");\n"
		text += "};\n\n"
		text += "#endif"
		return text

	def genReadonlyCPP(self):
		text = "#include \"" + self.nameRE + ".h\"\n\n"
		text += self.nameRE + "::" + self.nameRE + "() : Entity(){\n"
		for variable in self.variables:
			text += self.indent(1) + "this->" + variable + " = 0;\n"
		text += "}\n\n"
		text += "void " + self.nameRE + "::Update(int id, int x, int y"
		for argument in self.arguments:
			text += ", int " + argument
		text += "){\n"
		text += self.indent(1) + "Entity::Update(id, x, y);\n"
		for argument in self.arguments:
			text += self.indent(1) + "this->" + argument + " = " + argument + ";\n"
		text += "};"
		return text

	def genTemplateH(self):
		text = "#ifndef " + self.name.upper() + "_H\n"
		text += "#define " + self.name.upper() + "_H\n\n"
		text += "#include \"../../readonly/entities/" + self.nameRE + ".h\"\n\n"
		text += "class " + self.name + " : public " + self.nameRE + "{\n"
		text += self.indent(1) + "public:\n"
		text += self.indent(2) + self.name + "();\n"
		text += self.indent(1) + "private:\n"
		text += "};\n\n"
		text += "#endif"
		return text

	def genTemplateCPP(self):
		text = "#include \"" + self.name + ".h\"\n\n"
		text += self.name + "::" + self.name + "() : " + self.nameRE + "(){\n"
		text += "}";
		return text
