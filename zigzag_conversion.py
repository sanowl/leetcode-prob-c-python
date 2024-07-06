def convert(s: str, numRows: int) -> str:
    if numRows == 1 or numRows >= len(s):
        return s

    rows = [''] * numRows
    current_row = 0
    step = 1

    for char in s:
        rows[current_row] += char
        
        if current_row == 0:
            step = 1
        elif current_row == numRows - 1:
            step = -1
        
        current_row += step

    return ''.join(rows)

# Test the function
print(convert("PAYPALISHIRING", 3))  # Output: "PAHNAPLSIIGYIR"
print(convert("PAYPALISHIRING", 4))  # Output: "PINALSIGYAHRPI"
print(convert("A", 1))  # Output: "A"
