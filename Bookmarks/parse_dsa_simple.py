import re
import json
from bs4 import BeautifulSoup

def extract_dsa_content():
    """Extract DSA sheet content by directly parsing the HTML."""
    with open('DSA SHEET.html', 'r', encoding='utf-8') as file:
        content = file.read()
    
    soup = BeautifulSoup(content, 'html.parser')
    
    # Find all H3 elements and their associated content
    h3_elements = soup.find_all('h3')
    dsa_sections = []
    
    for h3 in h3_elements:
        title = h3.get_text(strip=True)
        
        # Skip the main DSA Sheet folder and Bookmarks Bar
        if title in ['DSA Sheet', 'Bookmarks Bar']:
            continue
        
        # This is a main section - collect all its links
        section_data = {
            'name': title,
            'type': 'folder',
            'items': []
        }
        
        # Find the DL element that contains the links for this section
        parent_dt = h3.find_parent('dt')
        if parent_dt:
            # Look for DL within this DT or as next sibling
            section_dl = parent_dt.find('dl')
            if section_dl:
                section_data['items'] = extract_section_content(section_dl)
        
        dsa_sections.append(section_data)
    
    return dsa_sections

def extract_section_content(dl_element):
    """Extract content from a DL section recursively."""
    items = []
    
    # Find all DT elements within this DL
    dt_elements = dl_element.find_all('dt')
    
    for dt in dt_elements:
        # Skip DT elements that are nested within other DT elements
        # Only process direct children
        if dt.find_parent('dl') != dl_element:
            continue
            
        # Check if it has H3 (folder) or A (link)
        h3 = dt.find('h3', recursive=False)
        a = dt.find('a', recursive=False)
        
        if h3:
            # It's a folder
            folder_name = h3.get_text(strip=True)
            sub_dl = dt.find('dl')
            sub_items = extract_section_content(sub_dl) if sub_dl else []
            
            items.append({
                'name': folder_name,
                'type': 'folder',
                'items': sub_items
            })
        elif a:
            # It's a link
            link_name = a.get_text(strip=True)
            link_url = a.get('href', '')
            
            items.append({
                'name': link_name,
                'type': 'link',
                'url': link_url
            })
    
    return items

def main():
    try:
        print("Extracting DSA content...")
        dsa_data = extract_dsa_content()
        
        # Save to JSON
        with open('dsa_data_simple.json', 'w', encoding='utf-8') as file:
            json.dump(dsa_data, file, indent=2, ensure_ascii=False)
        
        print(f"Successfully extracted {len(dsa_data)} main sections:")
        
        for section in dsa_data:
            print(f"- {section['name']}: {len(section['items'])} items")
        
        print(f"\nData saved to dsa_data_simple.json")
        
    except Exception as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    main()