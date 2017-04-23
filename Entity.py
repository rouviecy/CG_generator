from Extractor import Extractor

class Entity:
	
	def __init__(self, entity):
		self.entity = entity
		self.name = None
		self.dico = None
		self.arguments = []
		self.variables = []

	def decode(self, bloc):
		self.name = Extractor.extractParam('name', bloc)
		self.dico = Extractor.extractParam('dico', bloc)
		self.arguments = Extractor.extractList('args', bloc)
		self.variables = Extractor.extractList('vars', bloc)
