import os
import sys
from collections import Counter

INPUT_FILE = os.path.join(sys.path[0], 'inputs/i1.txt')

def calculate_similarity(filepath):
    """Calculates the sum of absolute differences and a similarity score from a file.
    This implementation was enhanced with the help of Gemini 2.0. At first, it did
    not recognize that Counter should be tracking n2. Gemini 1.5 produced incorrect
    outputs for both parts of the problem.

    Args:
        filepath: Path to the input file.

    Returns:
        A tuple containing the sum of absolute differences and the similarity score.
        Returns None if there is an error reading the file.
    """
    try:
        with open(filepath, 'r') as file:
            nums1 = []
            nums2 = []
            counts = Counter()  # Use Counter for efficient counting

            for line in file:
                n1, n2 = map(int, line.strip().split()) # Directly convert to int
                nums1.append(n1)
                nums2.append(n2)
                counts[n2] += 1

        if not nums1 or not nums2: #check if the file is empty
            return 0, 0

        sum_diff = sum(abs(n1 - n2) for n1, n2 in zip(sorted(nums1), sorted(nums2)))
        sim_score = sum(num * counts[num] for num in nums1)

        return sum_diff, sim_score

    except FileNotFoundError:
        print(f"Error: File not found: {filepath}", file=sys.stderr)
        return None
    except ValueError:
        print(f"Error: Invalid input format in: {filepath}", file=sys.stderr)
        return None
    except Exception as e:
        print(f"An unexpected error occurred: {e}", file=sys.stderr)
        return None



if __name__ == "__main__":
    result = calculate_similarity(INPUT_FILE)
    if result:
        sum_diff, sim_score = result
        print(sum_diff)
        print(sim_score)
