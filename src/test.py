
mat = [
    [0,  -1,  -2,  -3], 
    [-1,   3,   1,  -1],
    [-2,   1,   6,   4], 
    [-3,  -1,   4,   5], 
    [-4,  -3,   2,   3]
]

top = "why"
sid = "what"

align = []

i = len(sid)
j = len(top)

A = ""
B = ""

while i > 0 and j > 0:
    if mat[i][j] == mat[i-1][j] - 2:
        A = sid[i-1] + A
        B = '-' + B
        i -= 1
    elif mat[i][j] == mat[i][j-1] - 2:
        A = '-' + A
        B = top[j-1] + B
        j -= 1
    else:
        A = sid[i-1] + A
        B = top[j-1] + B
        j -= 1
        i -= 1

while i > 0:
    B = '-' + B
    A = sid[i-1] + A
    i -= 1

while j > 0:
    A = '-' + A
    B = top[j-1] + B
    j -= 1


al = []

def find(M, i, j, A, B, top, sid):
    pos = []
    n = 0

    if i > 0 and j > 0:
        if mat[i][j] == mat[i-1][j] - 2:
            A1 = sid[i-1] + A
            B1 = '-' + B
            pos += find(M, i-1, j, A1, B1, top, sid)
        
        if mat[i][j] == mat[i][j-1] - 2:
            A2 = '-' + A
            B2 = top[j-1] + B
            pos += find(M, i, j-1, A2, B2, top, sid)    
        
        if mat[i][j] in (mat[i-1][j-1]-1, mat[i-1][j-1]+3):
            A3 = sid[i-1] + A
            B3 = top[j-1] + B
            pos += find(M, i-1, j-1, A3, B3, top, sid)

        return pos
    else:
        while i > 0:
            A = sid[i-1] + A
            B = '-' + B
            i -= 1

        while j > 0:
            A = '-' + A
            B = top[j-1] + B
            j -= 1

        return [(A, B)]

# print(A)
# print(B)
print(find(mat, len(sid), len(top), "", "", top, sid))

def find2(M, i, j, A, B, top, sid, al):
    n = 0
    pos = []

    if i > 0 and j > 0:
        if mat[i][j] == mat[i-1][j] - 2:
            A1 = sid[i-1] + A
            B1 = '-' + B
            find2(M, i-1, j, A1, B1, top, sid, pos)
        
        if mat[i][j] == mat[i][j-1] - 2:
            A2 = '-' + A
            B2 = top[j-1] + B
            find2(M, i, j-1, A2, B2, top, sid, pos)
        
        if mat[i][j] in (mat[i-1][j-1]-1, mat[i-1][j-1]+3):
            A3 = sid[i-1] + A
            B3 = top[j-1] + B
            find2(M, i-1, j-1, A3, B3, top, sid, pos)

        for p in pos:
            al.append(p)
    else:
        while i > 0:
            A = sid[i-1] + A
            B = '-' + B
            i -= 1

        while j > 0:
            A = '-' + A
            B = top[j-1] + B
            j -= 1

        al.append((A, B))

al2 = []
find2(mat, len(sid), len(top), "", "", top, sid, al2)
print(al2)
