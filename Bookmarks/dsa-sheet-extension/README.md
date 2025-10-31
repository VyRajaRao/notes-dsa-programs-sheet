# DSA Sheet Navigator - Chrome Extension

A comprehensive Chrome extension that provides quick access to your complete Data Structures & Algorithms study materials with hierarchical navigation and powerful search functionality.

## Features

- 🗂️ **Hierarchical Navigation**: Browse through 200+ DSA topics organized in a clean, expandable tree structure
- 🔍 **Powerful Search**: Instantly search through thousands of problems and topics with highlighted results
- 📚 **Categorized Content**: Topics are intelligently grouped into:
  - Fundamentals (Getting Started, Time & Space Complexity, etc.)
  - Data Structures (Arrays, Trees, Graphs, etc.)
  - Algorithms (Sorting, Binary Search, Dynamic Programming, etc.)
  - Advanced Topics (Competitive Programming, etc.)
- 📊 **Statistics**: See total count of topics and problems at a glance
- 🎯 **Direct Access**: Click any problem to open it in a new tab
- 💫 **Responsive Design**: Clean, modern interface that works seamlessly

## Installation

### Method 1: Load as Unpacked Extension (Recommended for Development)

1. **Download the Extension**
   - Download or clone this repository
   - Extract the `dsa-sheet-extension` folder to your desired location

2. **Add Icons (Required)**
   - Create icon files: `icon16.png`, `icon48.png`, `icon128.png`
   - Place them in the `dsa-sheet-extension/icons/` folder
   - See `icons/ICON_INSTRUCTIONS.txt` for detailed guidance

3. **Load in Chrome**
   - Open Chrome and navigate to `chrome://extensions/`
   - Enable "Developer mode" (toggle in top-right corner)
   - Click "Load unpacked"
   - Select the `dsa-sheet-extension` folder
   - The extension will be installed and pinned to your toolbar

### Method 2: Create CRX Package (For Distribution)

1. Follow steps 1-2 from Method 1
2. In `chrome://extensions/`, click "Pack extension"
3. Select the `dsa-sheet-extension` folder
4. Chrome will generate a `.crx` file and private key
5. Share the `.crx` file for easy installation

## Usage

### Basic Navigation
1. **Click the extension icon** in your Chrome toolbar
2. **Browse categories**: Click on folder icons to expand/collapse sections
3. **Open problems**: Click on any problem to open it in a new tab
4. **View statistics**: See total topics and problems count at the bottom

### Search Functionality
1. **Type in the search box** to find specific topics or problems
2. **Real-time results**: See matching results as you type
3. **Highlighted matches**: Search terms are highlighted in results
4. **Click to open**: Click any search result to open the link
5. **Clear search**: Use the X button or press Escape to clear

### Tips for Best Experience
- **Pin the extension**: Right-click the extension icon → "Pin" for easy access
- **Use keyboard shortcuts**: Type to search, Escape to clear
- **Explore categories**: Each main category contains multiple sub-topics
- **Bookmark frequently used**: Use Chrome's regular bookmarking for your most-used problems

## Content Overview

The extension includes comprehensive coverage of:

### Fundamentals (50+ topics)
- Getting Started with Programming
- Time & Space Complexity Analysis
- Basic Math Problems & Pattern Printing
- Number Theory & Modular Arithmetic

### Data Structures (80+ topics)
- Arrays & Strings (Matrix problems, String matching, etc.)
- Linked Lists (Design, manipulation, sorting)
- Stacks & Queues (Design, expression evaluation)
- Trees (Binary trees, BST, traversals, etc.)
- Heaps & Hashing (Priority queues, hash maps)

### Algorithms (100+ topics)
- Sorting Algorithms (All major sorting techniques)
- Binary Search (1D, 2D, search space techniques)
- Two Pointers & Sliding Window
- Recursion & Backtracking (N-Queens, Sudoku, etc.)
- Dynamic Programming (All major patterns)
- Greedy Algorithms
- Graph Algorithms (BFS, DFS, shortest paths, MST)

### Advanced Topics (50+ topics)
- Bit Manipulation & Bitmasking
- Advanced Trees (Segment trees, Fenwick trees)
- Competitive Programming techniques
- Network Flow Algorithms
- Advanced Mathematics

## Technical Details

- **Manifest Version**: 3 (Latest Chrome extension standard)
- **Permissions**: Minimal permissions required (no access to browsing data)
- **Size**: Lightweight (~500KB including all data)
- **Performance**: Fast search and navigation with optimized data structures
- **Compatibility**: Works with Chrome 88+ and Chromium-based browsers

## Customization

### Updating Content
1. Modify `data/dsa_data.json` to add/remove topics
2. Reload the extension in `chrome://extensions/`

### Styling
1. Edit `css/styles.css` to customize appearance
2. Colors, fonts, spacing can all be adjusted

### Functionality
1. Modify `js/popup.js` to add new features
2. The code is well-commented and modular

## Troubleshooting

### Extension Not Loading
- Ensure all required files are present
- Check that icons folder contains the required PNG files
- Verify manifest.json syntax is correct

### Search Not Working
- Check browser console for JavaScript errors
- Ensure dsa_data.json is valid JSON format

### Links Not Opening
- Verify URLs in the data file are complete and valid
- Check that Chrome popup blocker isn't interfering

## File Structure

```
dsa-sheet-extension/
├── manifest.json          # Extension configuration
├── popup.html             # Main popup interface
├── css/
│   └── styles.css         # All styling
├── js/
│   └── popup.js           # Main functionality
├── data/
│   └── dsa_data.json      # All DSA topics and links
├── icons/
│   ├── icon16.png         # Toolbar icon
│   ├── icon48.png         # Extension manager icon
│   └── icon128.png        # Chrome Web Store icon
└── README.md              # This file
```

## Contributing

1. Fork the repository
2. Add new features or fix bugs
3. Test thoroughly with different scenarios
4. Submit pull request with detailed description

## License

This project is open source and available under the MIT License.

## Support

If you encounter any issues or have suggestions for improvement:
1. Check the troubleshooting section above
2. Open an issue on the repository
3. Provide detailed information about your Chrome version and the problem

---

**Happy coding! 🚀**