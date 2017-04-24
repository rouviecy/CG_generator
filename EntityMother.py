from Indentable import Indentable

class EntityMother(Indentable):

	def __init__(self):
		pass

	def write(self, entities):
		readonlyH = open("./CPP/readonly/Entity_readonly.h", 'w')
		readonlyH.write(self.genReadonlyH())
		readonlyCPP = open("./CPP/readonly/Entity_readonly.cpp", 'w')
		readonlyCPP.write(self.genReadonlyCPP())
		templateH = open("./CPP/template/Entity.h", 'w')
		templateH.write(self.genTemplateH())
		templateCPP = open("./CPP/template/Entity.cpp", 'w')
		templateCPP.write(self.genTemplateCPP())

	def genReadonlyH(self):
		text = "#ifndef ENTITY_READONLY_H\n"
		text += "#define ENTITY_READONLY_H\n\n"
		text += "#include \"../custom/common.h\"\n"
		text += "\n"
		text += "class Entity_readonly{\n"
		text += self.indent(1) + "public:\n"
		text += self.indent(2) + "int id;\n"
		text += self.indent(2) + "int x;\n"
		text += self.indent(2) + "int y;\n"
		text += self.indent(2) + "Entity_readonly();\n"
		text += self.indent(2) + "Entity_readonly(int id, int x, int y);\n"
		text += self.indent(2) + "void Update(int id, int x, int y);\n"
		text += "};\n\n"
		text += "#endif"
		return text

	def genTemplateH(self):
		text = "#ifndef ENTITY_H\n"
		text += "#define ENTITY_H\n\n"
		text += "#include \"../readonly/Entity_readonly.h\"\n"
		text += "\n"
		text += "class Entity : public Entity_readonly{\n"
		text += self.indent(1) + "public:\n"
		text += self.indent(2) + "Entity();\n"
		text += self.indent(2) + "Entity(int id, int x, int y);\n"
		text += self.indent(2) + "void Update(int id, int x, int y);\n"
		text += self.indent(1) + "private:\n"
		text += "};\n\n"
		text += "#endif"
		return text
		
	def genReadonlyCPP(self):
		text = "#include \"./Entity_readonly.h\"\n"
		text += "\n"
		text += "Entity_readonly::Entity_readonly() : Entity_readonly(-1, 0, 0){}\n\n"
		text += "Entity_readonly::Entity_readonly(int id, int x, int y){\n"
		text += self.indent(1) + "Entity_readonly::Update(id, x, y);\n"
		text += "}\n\n"
		text += "void Entity_readonly::Update(int id, int x, int y){\n"
		text += self.indent(1) + "this->id = id;\n"
		text += self.indent(1) + "this->x = x;\n"
		text += self.indent(1) + "this->y = y;\n"
		text += "}"
		return text

	def genTemplateCPP(self):
		text = "#include \"./Entity.h\"\n"
		text += "\n"
		text += "Entity::Entity() : Entity_readonly(){}\n\n"
		text += "Entity::Entity(int id, int x, int y) : Entity_readonly(id, x, y){\n\n"
		text += "}\n\n"
		text += "void Entity::Update(int id, int x, int y){\n"
		text += self.indent(1) + "Entity_readonly::Update(id, x, y);\n\n"
		text += "}"
		return text
