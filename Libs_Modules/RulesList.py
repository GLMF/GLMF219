from Rule import Rule
import json

class RulesList:
    def __init__(self, filename : str, rules : list = []):
        self.filename = filename
        self.rules = rules

    def readRules(self) -> None:
        try:
            with open(self.filename) as data:
                self.rules = json.load(data)
        except Exception as e:
            print('Error while reading', self.filename, ':', e)


    def getRule(self) -> Rule:
        for rule in self.rules['rules']:
            yield Rule(rule['ruleName'], rule['patterns'], rule['responses'])

    def getUnknown(self) -> list:
        return self.rules['unknown']
