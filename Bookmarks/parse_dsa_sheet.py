import re
import json
from bs4 import BeautifulSoup

def parse_dsa_sheet(file_path):
    """Parse the DSA sheet HTML file and extract structured data."""
    with open(file_path, 'r', encoding='utf-8') as file:
        content = file.read()
    
    soup = BeautifulSoup(content, 'html.parser')
    
    def parse_bookmark_list(dl_element, level=0):
        """Recursively parse bookmark lists."""
        items = []
        
        if not dl_element:
            return items
        
        # In bookmark files, DT elements are often inside P tags within DL
        # So we need to look for DT elements within P tags or directly
        dt_elements = []
        
        # First, try to find DT elements directly
        direct_dt = dl_element.find_all('dt', recursive=False)
        if direct_dt:
            dt_elements = direct_dt
        else:
            # Look for P tags that might contain DT elements
            p_tags = dl_element.find_all('p', recursive=False)
            for p in p_tags:
                dt_elements.extend(p.find_all('dt', recursive=False))
        
        for dt in dt_elements:
            # Check if it's a folder (H3) or a link (A)
            h3 = dt.find('h3', recursive=False)  # Only direct H3, not nested ones
            a = dt.find('a', recursive=False)    # Only direct A, not nested ones
            
            if h3:
                # It's a folder
                folder_name = h3.get_text(strip=True)
                # Find the DL element for sub-items (usually the next sibling or within the DT)
                next_dl = dt.find('dl')
                sub_items = parse_bookmark_list(next_dl, level + 1) if next_dl else []
                
                items.append({
                    'type': 'folder',
                    'name': folder_name,
                    'level': level,
                    'items': sub_items
                })
            elif a:
                # It's a link
                link_name = a.get_text(strip=True)
                link_url = a.get('href', '')
                
                items.append({
                    'type': 'link',
                    'name': link_name,
                    'url': link_url,
                    'level': level
                })
        
        return items
    
    # Find the main DSA Sheet folder
    # Look for H3 with text "DSA Sheet" - this is the folder containing all DSA content
    all_h3 = soup.find_all('h3')
    
    for h3 in all_h3:
        if h3.get_text(strip=True) == 'DSA Sheet':
            # Get the parent DT element
            dsa_sheet_dt = h3.find_parent('dt')
            if dsa_sheet_dt:
                # Find the DL that comes after the H3 within this DT
                # This DL contains all the DSA sheet content
                dl_sibling = dsa_sheet_dt.find('dl')
                if dl_sibling:
                    return parse_bookmark_list(dl_sibling)
            break
    
    return []

def save_to_json(data, output_path):
    """Save parsed data to JSON file."""
    with open(output_path, 'w', encoding='utf-8') as file:
        json.dump(data, file, indent=2, ensure_ascii=False)

def debug_html_structure(file_path):
    """Debug the HTML structure to understand the layout."""
    with open(file_path, 'r', encoding='utf-8') as file:
        content = file.read()
    
    soup = BeautifulSoup(content, 'html.parser')
    
    # Find all H3 elements
    h3_elements = soup.find_all('h3')
    print("Found H3 elements:")
    for h3 in h3_elements[:10]:  # Show first 10
        print(f"  - {h3.get_text(strip=True)}")
    
    # Look for the DSA Sheet specifically and examine its structure
    for h3 in h3_elements:
        if h3.get_text(strip=True) == 'DSA Sheet':
            print(f"\nFound DSA Sheet H3 element:")
            parent_dt = h3.find_parent('dt')
            if parent_dt:
                print(f"  - Parent DT found")
                
                # Check for DL inside DT
                internal_dl = parent_dt.find('dl')
                if internal_dl:
                    # Check all children of the DL element
                    all_children = list(internal_dl.children)
                    print(f"  - Internal DL has {len(all_children)} direct children")
                    
                    # Look at the first few children and their types
                    for i, child in enumerate(all_children[:10]):
                        if hasattr(child, 'name') and child.name:
                            print(f"    Child {i+1}: {child.name} - '{str(child)[:50].strip()}'")
                        else:
                            print(f"    Child {i+1}: Text node - '{str(child).strip()[:50]}'")
                    
                    # Try to find DT elements by examining the actual structure
                    all_dt_children = internal_dl.find_all('dt')
                    direct_dt_children = internal_dl.find_all('dt', recursive=False)
                    print(f"  - Found {len(direct_dt_children)} direct DT children and {len(all_dt_children)} total DT children")
                else:
                    print(f"  - No internal DL found")
                
                # Check siblings
                next_sibling = parent_dt.find_next_sibling()
                if next_sibling and next_sibling.name == 'dl':
                    print(f"  - Next sibling DL found")
                else:
                    print(f"  - No next sibling DL found")
            break

def main():
    input_file = 'DSA SHEET.html'
    output_file = 'dsa_data.json'
    
    # Add debugging flag
    debug = True
    
    try:
        if debug:
            # Test with simple debugging
            with open(input_file, 'r', encoding='utf-8') as file:
                content = file.read()
            soup = BeautifulSoup(content, 'html.parser')
            
            # Find the DSA Sheet H3 and examine structure
            for h3 in soup.find_all('h3'):
                if h3.get_text(strip=True) == 'DSA Sheet':
                    parent_dt = h3.find_parent('dt')
                    if parent_dt:
                        internal_dl = parent_dt.find('dl')
                        if internal_dl:
                            p_tag = internal_dl.find('p')
                            if p_tag:
                                # Examine actual children of P tag
                                direct_children = list(p_tag.children)
                                print(f"P tag has {len(direct_children)} direct children")
                                
                                # Look at first 10 direct children
                                dt_count = 0
                                for i, child in enumerate(direct_children[:20]):
                                    if hasattr(child, 'name') and child.name == 'dt':
                                        dt_count += 1
                                        h3_child = child.find('h3', recursive=False)
                                        a_child = child.find('a', recursive=False)
                                        if h3_child:
                                            print(f"  DT {dt_count}: Folder: {h3_child.get_text(strip=True)}")
                                        elif a_child:
                                            print(f"  DT {dt_count}: Link: {a_child.get_text(strip=True)}")
                                    elif hasattr(child, 'name') and child.name:
                                        print(f"  Child {i+1}: {child.name} tag")
                                    else:
                                        text_content = str(child).strip()
                                        if text_content:
                                            print(f"  Child {i+1}: Text: '{text_content[:30]}...'")
                                        # else skip empty text nodes
                                
                                print(f"Total DT children found: {dt_count}")
                    break
        
        parsed_data = parse_dsa_sheet(input_file)
        save_to_json(parsed_data, output_file)
        print(f"\nSuccessfully parsed DSA sheet!")
        print(f"Found {len(parsed_data)} main sections")
        
        # Print summary
        for item in parsed_data:
            if item['type'] == 'folder':
                print(f"- {item['name']}: {len(item['items'])} sub-items")
            else:
                print(f"- {item['name']}: {item['url']}")
        
        print(f"\nData saved to {output_file}")
                
    except Exception as e:
        print(f"Error parsing DSA sheet: {e}")

if __name__ == "__main__":
    main()