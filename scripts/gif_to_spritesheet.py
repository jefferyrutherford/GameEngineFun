from PIL import Image, ImageSequence
import sys
import os

def gif_to_spritesheet(gif_path, output_path="spritesheet.png", frames_per_row=None):
    """
    Converts a GIF into a sprite sheet (PNG).
    
    Parameters:
        gif_path (str): Path to input GIF.
        output_path (str): Path to save the sprite sheet PNG.
        frames_per_row (int | None): Number of frames per row in the sheet.
                                     If None, all frames in one row.
    """
    # Load GIF
    gif = Image.open(gif_path)
    frames = [frame.copy().convert("RGBA") for frame in ImageSequence.Iterator(gif)]
    
    frame_width, frame_height = frames[0].size
    num_frames = len(frames)

    # Calculate grid layout
    if frames_per_row is None:
        frames_per_row = num_frames
    rows = (num_frames + frames_per_row - 1) // frames_per_row

    # Create blank spritesheet
    sheet_width = frames_per_row * frame_width
    sheet_height = rows * frame_height
    spritesheet = Image.new("RGBA", (sheet_width, sheet_height))

    # Paste frames
    for i, frame in enumerate(frames):
        x = (i % frames_per_row) * frame_width
        y = (i // frames_per_row) * frame_height
        spritesheet.paste(frame, (x, y))

    # Save result
    spritesheet.save(output_path)
    print(f"✅ Sprite sheet saved to {output_path}")


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python gif_to_spritesheet.py <input.gif> [output.png] [frames_per_row]")
    else:
        gif_path = sys.argv[1]
        output_path = sys.argv[2] if len(sys.argv) > 2 else "spritesheet.png"
        frames_per_row = int(sys.argv[3]) if len(sys.argv) > 3 else None
        gif_to_spritesheet(gif_path, output_path, frames_per_row)

