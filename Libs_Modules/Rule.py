class Rule:
    def __init__(self, ruleName : str, patterns : list = [], responses : list = []):
        self.ruleName = ruleName
        self.patterns = patterns
        self.responses = responses

    def getRuleName(self) -> str:
        return self.ruleName

    def getPatterns(self) -> list:
        return self.patterns

    def getResponses(self) -> list:
        return self.responses

    def __str__(self) -> str:
        return 'Rule(ruleName=\'{}\', patterns=\'{}\', responses=\'{}\')'.format(self.ruleName, self.patterns, self.responses)
