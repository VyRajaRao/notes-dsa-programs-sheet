// DSA Sheet Navigator - Main JavaScript
class DSANavigator {
    constructor() {
        this.dsaData = [];
        this.searchResults = [];
        this.expandedSections = new Set();
        
        this.initializeElements();
        this.setupEventListeners();
        this.loadDSAData();
    }

    initializeElements() {
        this.elements = {
            searchInput: document.getElementById('searchInput'),
            searchResults: document.getElementById('searchResults'),
            searchResultsList: document.getElementById('searchResultsList'),
            searchResultsCount: document.getElementById('searchResultsCount'),
            clearSearch: document.getElementById('clearSearch'),
            navigationMenu: document.getElementById('navigationMenu'),
            totalTopics: document.getElementById('totalTopics'),
            totalLinks: document.getElementById('totalLinks')
        };
    }

    setupEventListeners() {
        // Search functionality
        this.elements.searchInput.addEventListener('input', (e) => {
            this.handleSearch(e.target.value.trim());
        });

        // Clear search
        this.elements.clearSearch.addEventListener('click', () => {
            this.clearSearch();
        });

        // Handle keyboard navigation
        this.elements.searchInput.addEventListener('keydown', (e) => {
            if (e.key === 'Escape') {
                this.clearSearch();
            }
        });
    }

    async loadDSAData() {
        try {
            const response = await fetch(chrome.runtime.getURL('data/dsa_data.json'));
            this.dsaData = await response.json();
            
            this.renderNavigationMenu();
            this.updateStats();
        } catch (error) {
            console.error('Failed to load DSA data:', error);
            this.showError('Failed to load DSA topics. Please try again.');
        }
    }

    renderNavigationMenu() {
        const menu = this.elements.navigationMenu;
        menu.innerHTML = '';

        // Group main categories for better organization
        const mainCategories = this.organizeCategories(this.dsaData);
        
        mainCategories.forEach((category, index) => {
            const section = this.createNavigationSection(category, index);
            menu.appendChild(section);
        });
    }

    organizeCategories(data) {
        // Group related categories together
        const categoryGroups = {
            'Fundamentals': ['Getting Started', 'Time & Space Complexity', 'Basic Math Problems', 'Pattern Printing'],
            'Data Structures': ['Arrays & Strings', 'Linked List', 'Stack & Queue', 'Trees', 'Hashmap & Heaps'],
            'Algorithms': ['Sorting Algorithms', 'Binary Search', 'Two Pointer Technique', 'Greedy Algorithms'],
            'Advanced Topics': ['Dynamic Programming', 'Recursion & Backtracking', 'Graphs', 'Number Theory', 'Bit Manipulation'],
            'Specialized': ['Competitive Programming', 'Advanced Trees', 'Network Flow Algorithm']
        };

        const organized = [];
        const used = new Set();

        // Add categorized items
        Object.entries(categoryGroups).forEach(([groupName, categories]) => {
            const groupItems = data.filter(item => {
                return categories.some(cat => item.name.includes(cat) || cat.includes(item.name));
            });

            if (groupItems.length > 0) {
                organized.push({
                    name: groupName,
                    type: 'group',
                    items: groupItems,
                    isGroup: true
                });

                groupItems.forEach(item => used.add(item.name));
            }
        });

        // Add remaining items
        const remaining = data.filter(item => !used.has(item.name));
        if (remaining.length > 0) {
            organized.push({
                name: 'Other Topics',
                type: 'group',
                items: remaining,
                isGroup: true
            });
        }

        return organized.length > 0 ? organized : data;
    }

    createNavigationSection(section, index) {
        const sectionDiv = document.createElement('div');
        sectionDiv.className = 'nav-section';

        if (section.isGroup) {
            // Create group header
            const groupHeader = document.createElement('div');
            groupHeader.className = 'nav-item group-header';
            groupHeader.innerHTML = `
                <div class="nav-icon">📚</div>
                <div class="nav-content">
                    <div class="nav-title">${section.name}</div>
                    <div class="nav-count">${section.items.length} categories</div>
                </div>
                <div class="expand-icon">▶</div>
            `;

            const submenu = document.createElement('div');
            submenu.className = 'nav-submenu';
            submenu.id = `group-${index}`;

            // Add group items
            section.items.forEach((item, itemIndex) => {
                const itemElement = this.createNavigationItem(item, `${index}-${itemIndex}`);
                submenu.appendChild(itemElement);
            });

            groupHeader.addEventListener('click', () => {
                this.toggleSection(groupHeader, submenu);
            });

            sectionDiv.appendChild(groupHeader);
            sectionDiv.appendChild(submenu);
        } else {
            // Regular item
            const item = this.createNavigationItem(section, index);
            sectionDiv.appendChild(item);
        }

        return sectionDiv;
    }

    createNavigationItem(item, id) {
        const itemDiv = document.createElement('div');
        itemDiv.className = 'nav-item';
        itemDiv.dataset.id = id;

        const hasSubItems = item.items && item.items.length > 0;
        const linkCount = this.countLinks(item);

        itemDiv.innerHTML = `
            <div class="nav-icon">${item.type === 'folder' ? '📁' : '🔗'}</div>
            <div class="nav-content">
                <div class="nav-title">${item.name}</div>
                <div class="nav-count">${linkCount} problems</div>
            </div>
            ${hasSubItems ? '<div class="expand-icon">▶</div>' : '<div class="link-indicator">↗</div>'}
        `;

        if (hasSubItems) {
            const submenu = document.createElement('div');
            submenu.className = 'nav-submenu';
            submenu.id = `submenu-${id}`;

            item.items.forEach((subItem, subIndex) => {
                const subItemElement = this.createSubNavigationItem(subItem, `${id}-${subIndex}`, 1);
                submenu.appendChild(subItemElement);
            });

            itemDiv.addEventListener('click', () => {
                this.toggleSection(itemDiv, submenu);
            });

            const wrapper = document.createElement('div');
            wrapper.appendChild(itemDiv);
            wrapper.appendChild(submenu);
            return wrapper;
        } else if (item.url) {
            itemDiv.addEventListener('click', () => {
                this.openLink(item.url, item.name);
            });
        }

        return itemDiv;
    }

    createSubNavigationItem(item, id, level) {
        const itemDiv = document.createElement('div');
        itemDiv.className = `nav-subitem level-${level}`;
        itemDiv.dataset.id = id;

        const hasSubItems = item.items && item.items.length > 0;
        const linkCount = this.countLinks(item);

        itemDiv.innerHTML = `
            <div class="nav-icon">${item.type === 'folder' ? '📂' : '🔗'}</div>
            <div class="nav-content">
                <div class="nav-title">${item.name}</div>
                ${linkCount > 0 ? `<div class="nav-count">${linkCount} problems</div>` : ''}
            </div>
            ${hasSubItems ? '<div class="expand-icon">▶</div>' : ''}
        `;

        if (hasSubItems) {
            const submenu = document.createElement('div');
            submenu.className = 'nav-submenu';
            submenu.id = `submenu-${id}`;

            item.items.forEach((subItem, subIndex) => {
                const subItemElement = this.createSubNavigationItem(subItem, `${id}-${subIndex}`, level + 1);
                submenu.appendChild(subItemElement);
            });

            itemDiv.addEventListener('click', () => {
                this.toggleSection(itemDiv, submenu);
            });

            const wrapper = document.createElement('div');
            wrapper.appendChild(itemDiv);
            wrapper.appendChild(submenu);
            return wrapper;
        } else if (item.url) {
            itemDiv.addEventListener('click', () => {
                this.openLink(item.url, item.name);
            });
        }

        return itemDiv;
    }

    toggleSection(headerElement, submenu) {
        const isExpanded = headerElement.classList.contains('expanded');
        
        if (isExpanded) {
            headerElement.classList.remove('expanded');
            submenu.classList.remove('expanded');
        } else {
            headerElement.classList.add('expanded');
            submenu.classList.add('expanded');
        }
    }

    countLinks(item) {
        if (!item || !item.items) {
            return item && item.url ? 1 : 0;
        }

        let count = 0;
        for (const subItem of item.items) {
            if (subItem.type === 'link' && subItem.url) {
                count++;
            } else if (subItem.type === 'folder') {
                count += this.countLinks(subItem);
            }
        }

        return count;
    }

    handleSearch(query) {
        if (!query || query.length < 2) {
            this.hideSearchResults();
            return;
        }

        const results = this.searchDSAData(query);
        this.displaySearchResults(results, query);
    }

    searchDSAData(query) {
        const results = [];
        const searchTerm = query.toLowerCase();

        const searchInItem = (item, path = []) => {
            const itemPath = [...path, item.name];
            
            // Check if current item matches
            if (item.name.toLowerCase().includes(searchTerm)) {
                results.push({
                    item: item,
                    path: itemPath.join(' › '),
                    matchType: 'name'
                });
            }

            // Search in sub-items
            if (item.items) {
                item.items.forEach(subItem => {
                    searchInItem(subItem, itemPath);
                });
            }
        };

        this.dsaData.forEach(item => searchInItem(item));

        return results.slice(0, 50); // Limit results
    }

    displaySearchResults(results, query) {
        this.elements.searchResults.classList.remove('hidden');
        this.elements.searchResultsCount.textContent = `${results.length} result${results.length !== 1 ? 's' : ''} found`;

        const resultsList = this.elements.searchResultsList;
        resultsList.innerHTML = '';

        if (results.length === 0) {
            resultsList.innerHTML = `
                <div class="search-result-item">
                    <div class="search-result-icon">🔍</div>
                    <div class="search-result-content">
                        <div class="search-result-title">No results found</div>
                        <div class="search-result-path">Try different keywords or browse categories</div>
                    </div>
                </div>
            `;
            return;
        }

        results.forEach(result => {
            const resultDiv = document.createElement('div');
            resultDiv.className = 'search-result-item';
            
            const icon = result.item.type === 'folder' ? '📁' : '🔗';
            const title = this.highlightMatch(result.item.name, query);
            
            resultDiv.innerHTML = `
                <div class="search-result-icon">${icon}</div>
                <div class="search-result-content">
                    <div class="search-result-title">${title}</div>
                    <div class="search-result-path">${result.path}</div>
                </div>
            `;

            if (result.item.url) {
                resultDiv.addEventListener('click', () => {
                    this.openLink(result.item.url, result.item.name);
                    this.clearSearch();
                });
            }

            resultsList.appendChild(resultDiv);
        });
    }

    highlightMatch(text, query) {
        const regex = new RegExp(`(${query.replace(/[.*+?^${}()|[\]\\]/g, '\\$&')})`, 'gi');
        return text.replace(regex, '<span class="highlight">$1</span>');
    }

    hideSearchResults() {
        this.elements.searchResults.classList.add('hidden');
    }

    clearSearch() {
        this.elements.searchInput.value = '';
        this.hideSearchResults();
        this.elements.searchInput.focus();
    }

    openLink(url, title) {
        chrome.tabs.create({ url: url, active: true });
        
        // Optional: Track usage
        console.log(`Opened: ${title} - ${url}`);
    }

    updateStats() {
        const totalTopics = this.dsaData.length;
        const totalLinks = this.dsaData.reduce((sum, item) => sum + this.countLinks(item), 0);

        this.elements.totalTopics.textContent = `${totalTopics} topics`;
        this.elements.totalLinks.textContent = `${totalLinks} problems`;
    }

    showError(message) {
        this.elements.navigationMenu.innerHTML = `
            <div class="loading-indicator">
                <div class="nav-icon">⚠️</div>
                <span>${message}</span>
            </div>
        `;
    }
}

// Initialize the extension when DOM is loaded
document.addEventListener('DOMContentLoaded', () => {
    new DSANavigator();
});