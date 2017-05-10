from Extractor import Extractor

class Global:
	
	def __init__(self, workspace):
		self.workspace = workspace
		self.excludes = []
		self.includes = []
		self.namespaces = []
		self.magicMap = False
		self.defines = []

	def decode(self, bloc):
		self.excludes = Extractor.extractList('exclude', bloc)
		self.includes = Extractor.extractList('include', bloc)
		self.namespaces = Extractor.extractList('namespace', bloc)
		self.magicMap = Extractor.extractBoolean('magicMap', bloc)
		self.defines = Extractor.extractList('define', bloc)

	def write(self, entities):
		readonlyH = open(self.workspace + "readonly/common_readonly.h", 'w')
		readonlyH.write(self.genReadonlyH(entities))
		templateH = open(self.workspace + "template/common.h", 'w')
		templateH.write(self.genTemplateH())

	def genReadonlyH(self, entities):
		text = "#ifndef COMMON_READONLY_H\n"
		text += "#define COMMON_READONLY_H\n\n"
		text += "#ifndef EXPLICITE_EXCLUDE\n"
		for exclude in self.excludes:
			text += "#include <" + exclude + ">\n"
		text += "#endif\n"
		for include in self.includes:
			text += "#include <" + include + ">\n"
		text += "\n"
		for namespace in self.namespaces:
			text += "using namespace " + namespace + ";\n"
		text += "\n"
		if self.magicMap:
			text += "#define forMap(type1, type2, it, carte) for(map<type1,type2>::iterator it = carte.begin(); it != carte.end(); ++it)\n"
			text += "#define forMapTypename(type1, type2, it, carte) for(typename map<type1,type2>::iterator it = carte.begin(); it != carte.end(); ++it)\n\n"
		for defineKey in self.defines.keys():
			text += "#define " + defineKey + " " + str(self.defines[defineKey]) + "\n"
		text += "\n"
		text += "class Game;\nclass Entity;\n"
		for entity in entities:
			text += "class " + entity.name + ";\n"
		text += "\n"
		text += "#endif"
		return text

	def genTemplateH(self):
		text = "#include \"../readonly/common_readonly.h\"\n"
		return text

	def genExcludedIncludes(self):
		text = ""
		for exclude in self.excludes:
			text += "#include <" + exclude + ">\n"
		return text
