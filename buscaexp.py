def busca_exponencial(lista, alvo):
    if lista[0] == alvo:
        return 0
    
    n = len(lista)
    i = 1
    
    while i < n and lista[i] <= alvo:
        i = i * 2
    
    return busca_binaria(lista, alvo, i // 2, min(i, n - 1))

def busca_binaria(lista, alvo, esquerda, direita):
    if direita >= esquerda:
        meio = esquerda + (direita - esquerda) // 2
        
        if lista[meio] == alvo:
            return meio
        
        if lista[meio] > alvo:
            return busca_binaria(lista, alvo, esquerda, meio - 1)
        
        return busca_binaria(lista, alvo, meio + 1, direita)
    
    return -1
