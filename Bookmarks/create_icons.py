from PIL import Image, ImageDraw, ImageFont
import os

def create_icon(size, filename):
    """Create a simple DSA-themed icon."""
    # Create a square image with gradient background
    img = Image.new('RGBA', (size, size), (0, 0, 0, 0))
    draw = ImageDraw.Draw(img)
    
    # Create gradient background (blue to purple)
    for y in range(size):
        # Calculate color based on position
        ratio = y / size
        r = int(102 + (118 - 102) * ratio)  # 667eea to 764ba2
        g = int(126 + (75 - 126) * ratio)
        b = int(234 + (162 - 234) * ratio)
        
        draw.line([(0, y), (size, y)], fill=(r, g, b, 255))
    
    # Add rounded corners
    mask = Image.new('L', (size, size), 0)
    mask_draw = ImageDraw.Draw(mask)
    corner_radius = size // 8
    mask_draw.rounded_rectangle([0, 0, size, size], corner_radius, fill=255)
    
    # Apply mask
    result = Image.new('RGBA', (size, size), (0, 0, 0, 0))
    result.paste(img, (0, 0))
    result.putalpha(mask)
    
    # Add DSA text or symbol
    try:
        # Try to load a font
        if size >= 32:
            font_size = size // 4
            try:
                font = ImageFont.truetype("arial.ttf", font_size)
            except:
                font = ImageFont.load_default()
        else:
            font = ImageFont.load_default()
            
        # Draw text
        text = "DSA"
        if size >= 32:
            # Get text bbox
            bbox = draw.textbbox((0, 0), text, font=font)
            text_width = bbox[2] - bbox[0]
            text_height = bbox[3] - bbox[1]
            
            x = (size - text_width) // 2
            y = (size - text_height) // 2
            
            # Draw text with shadow
            draw.text((x + 1, y + 1), text, fill=(0, 0, 0, 128), font=font)
            draw.text((x, y), text, fill=(255, 255, 255, 255), font=font)
        else:
            # For smaller icons, just draw a simple symbol
            center = size // 2
            radius = size // 3
            
            # Draw a tree-like structure
            draw.ellipse([center - 2, center - radius, center + 2, center - radius + 4], fill=(255, 255, 255, 255))
            draw.ellipse([center - radius//2, center - radius//2, center + radius//2, center + radius//2], fill=(255, 255, 255, 255))
            
    except Exception as e:
        print(f"Error adding text to {filename}: {e}")
    
    return result

def main():
    """Create all required icons."""
    output_dir = "dsa-sheet-extension/icons"
    
    # Ensure output directory exists
    os.makedirs(output_dir, exist_ok=True)
    
    # Create icons
    sizes = [16, 48, 128]
    
    for size in sizes:
        print(f"Creating icon{size}.png...")
        icon = create_icon(size, f"icon{size}.png")
        icon.save(os.path.join(output_dir, f"icon{size}.png"), "PNG")
    
    print("Icons created successfully!")
    print(f"Icons saved in: {output_dir}")

if __name__ == "__main__":
    main()