import os

def create_nested_folders(base_path, depth, width):
    if depth == 0:
        return
    for i in range(width):
        new_dir = os.path.join(base_path, f"dir_{depth}_{i}")
        os.makedirs(new_dir, exist_ok=True)
        create_nested_folders(new_dir, depth - 1, width)

if __name__ == "__main__":
    base_path = "/home/mtoia/Desktop/ft_ls/test_inception"
    depth = 20  # Adjust the depth as needed
    width = 2   # Adjust the width as needed
    create_nested_folders(base_path, depth, width)