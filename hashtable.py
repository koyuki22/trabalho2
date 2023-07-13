class HashTable:
    def __init__(self):
        self.size = 10
        self.table = [[] for _ in range(self.size)]

    def _hash_function(self, key):
        # Calcula o índice da chave usando uma função de hash simples
        return hash(key) % self.size

    def insert(self, key, value):
        index = self._hash_function(key)
        self.table[index].append((key, value))

    def get(self, key):
        index = self._hash_function(key)
        values = self.table[index]
        for k, v in values:
            if k == key:
                return v
        raise KeyError("Chave não encontrada na tabela hash.")

    def remove(self, key):
        index = self._hash_function(key)
        values = self.table[index]
        for i, (k, v) in enumerate(values):
            if k == key:
                del self.table[index][i]
                return
        raise KeyError("Chave não encontrada na tabela hash.")