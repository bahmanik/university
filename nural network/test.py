import numpy as np
D = -0.5
I = 0.5

# Define two matrices
matrix1 = np.array([[I, D, D], [D, I, D], [D, D, I]])
matrix2 = np.array([[2], [2], [2]])

# Multiply the matrices
result = np.dot(matrix1, matrix2)

# Alternatively, you can use the @ operator
# result = matrix1 @ matrix2

print(matrix2)
print("\n")
print(result)
print("\n")
print(np.dot(matrix1, result))
result = np.dot(matrix1, result)
print("\n")
print(np.dot(matrix1, result))


