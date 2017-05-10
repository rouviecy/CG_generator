import re, ast

class Extractor:

	# Cherche si un bloc est d'un certain type à partir de son titre ; retourne le nom du bloc le cas échéant
	def extractBloc(blocType, text):
		regex = re.compile(blocType + '[ ]*(.*):', re.I)
		match = regex.search(text)
		if match:
			return match.group(1)
		else:
			return None

	# Cherche si un paramètre texte existe ; retourne sa valeur textuelle le cas échéant
	def extractParam(paramName, text):
		regex = re.compile(paramName + '[ ]*\=[ ]*(.*)', re.I)
		match = regex.search(text)
		if match:
			return match.group(1)
		return None

	# Cherche si un paramètre bool existe : retourne sa valeur booleenne le cas échant
	def extractBoolean(booleanName, text):
		extrait = Extractor.extractParam(booleanName, text)
		if extrait == None:
			return False
		return extrait.lower() in ['true', '1']

	# Cherche si un paramètre liste existe : retourne ses éléments le cas échéant
	def extractList(listName, text):
		extrait = Extractor.extractParam(listName, text)
		if extrait == None:
			return []
		return ast.literal_eval(extrait)
