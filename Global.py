from Extractor import Extractor

class Global:
	
	def __init__(self):
		self.includes = []
		self.namespaces = []
		self.magicMap = False
		self.defines = []

	def decode(self, bloc):
		self.includes = Extractor.extractList('include', bloc)
		self.namespaces = Extractor.extractList('namespace', bloc)
		self.magicMap = Extractor.extractBoolean('magicMap', bloc)
		self.defines = Extractor.extractList('define', bloc)

