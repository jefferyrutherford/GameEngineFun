from PIL import Image
import sys
import os

# Usage: python gif_to_spritesheet.py input.gif output.png
if len(sys.argv) != 3:
    print("Usage: python gif_to_spritesheet.py <input.gif> <output.png>")
    sys.exit(1)

input_gif = sys.argv[1]
output_png = sys.argv[2]

# Load the GIF
gif = Image.open(input_gif)

frames = []
try:
    while True:
        frame = gif.copy().convert("RGBA")  # Ensure proper format
        frames.append(frame)
        gif.seek(gif.tell() + 1)
except EOFError:
    pass  # End of frames

# Compute sprite sheet size (horizontal layout)
frame_width, frame_height = frames[0].size
sheet_width = frame_width * len(frames)
sheet_height = frame_height

# Create empty sprite sheet
spritesheet = Image.new("RGBA", (sheet_width, sheet_height))

# Paste frames into the sheet
for i, frame in enumerate(frames):
    spritesheet.paste(frame, (i * frame_width, 0))

# Save the sprite sheet
spritesheet.save(output_png)
print(f"Sprite sheet saved to {output_png} ({len(frames)} frames)")

