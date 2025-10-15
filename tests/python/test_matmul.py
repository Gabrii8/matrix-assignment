from src.python.matmul import matmul

def test_2x2_known():
    A = [[1, 2],
         [3, 4]]
    B = [[5, 6],
         [7, 8]]
    C = matmul(A, B)
    assert C == [[19, 22],
                 [43, 50]]

def test_identity():
    I = [[1, 0],
         [0, 1]]
    X = [[2, 3],
         [4, 5]]
    C = matmul(X, I)
    assert C == X

def test_zero_matrix():
    Z = [[0, 0], [0, 0]]
    X = [[1, 2], [3, 4]]
    C = matmul(X, Z)
    assert C == [[0, 0], [0, 0]]