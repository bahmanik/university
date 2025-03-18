import numpy as np

# Define the binary patterns
p1 = np.array([1, 0])
p2 = np.array([0, 1])
p3 = np.array([1, 1])

# Function to convert binary (0/1) to bipolar (1, -1)
def binary_to_bipolar(p):
    return np.where(p == 0, -1, 1)

# Convert the patterns
bp1 = binary_to_bipolar(p1)
bp2 = binary_to_bipolar(p2)
bp3 = binary_to_bipolar(p3)

print("Bipolar patterns:")
print("p1:", bp1)
print("p2:", bp2)
print("p3:", bp3)

# -------------------------------
# First Tier: Hamming Layer
# -------------------------------

W = np.array([bp1, bp2, bp3])  # Each row corresponds to one stored pattern.
b = 1  # bias value

print("\nFirst Tier (Correlation Layer):")
print("Weight matrix (W):")
print(W)
print("Bias (b):", b)

# Define a function for the first layer activation
def layer1_activation(x):
    # For an input x (assumed to be in bipolar form),
    # compute the dot product with each weight row and add the bias.
    return np.dot(W, x) + b

# Test first layer responses for each input pattern
def test_layer1(x, label):
    activation = layer1_activation(x)
    print(f"Activation for input {label} ({x}): {activation}")

print("\n--- First Layer Activations ---")
test_layer1(bp1, "p1")
test_layer1(bp2, "p2")
test_layer1(bp3, "p3")

# -------------------------------
# Second Tier: Winner-Takes-All
# -------------------------------

def winner_take_all(activations):
    output = np.zeros_like(activations)
    winner_index = np.argmax(activations)
    output[winner_index] = 1
    return output

# Define the full network function that processes an input pattern through both tiers.
def hamming_network(x, label):
    # First layer processing:
    a1 = layer1_activation(x)
    # Second layer (WTA):
    output = winner_take_all(a1)
    print(f"\nInput {label}: {x}")
    print("First layer activation:", a1)
    print("Network output (one-hot):", output)
    return output

print("\n--- Full Network Outputs ---")
hamming_network(bp1, "p1")
hamming_network(bp2, "p2")
hamming_network(bp3, "p3")

