/**
 * Banking System - Frontend Application
 * With NBP live rates, demo login, phone formatting, i18n
 */

// ============================================
// Internationalization (i18n)
// ============================================

const translations = {
    en: {
        // Login screen
        loginTitle: 'BankSystem',
        loginSubtitle: 'Select user profile',
        loginAdmin: 'Administrator',
        loginAdminDesc: 'Full system access',
        loginCompany: 'Company',
        loginCompanyDesc: 'TechCorp Sp. z o.o.',
        loginClient: 'Client',
        loginClientDesc: 'Jan Kowalski',
        loginFooter: 'Demo version - no authentication',
        
        // Navigation
        navDashboard: 'Dashboard',
        navBanks: 'Banks',
        navClients: 'Clients',
        navAccounts: 'My Accounts',
        navAllAccounts: 'All Accounts',
        navTransfers: 'Transfers',
        navMarket: 'Market',
        
        // Dashboard
        titleDashboard: 'Dashboard',
        titleBanks: 'Banks',
        titleClients: 'Clients',
        titleAccounts: 'Accounts',
        titleTransfers: 'Transfers',
        titleMarket: 'Market',
        
        // Stats
        statBanks: 'Banks',
        statClients: 'Clients',
        statAccounts: 'Accounts',
        statMyAccounts: 'My Accounts',
        statBalance: 'Total Balance',
        statMyBalance: 'My Balance',
        
        // Cards
        cardBanksOverview: 'Banks Overview',
        cardMyAccounts: 'My Accounts',
        cardExchangeRates: 'Exchange Rates',
        cardBanksList: 'Banks List',
        cardClientsList: 'Clients List',
        cardAccountsList: 'Accounts List',
        cardNewTransfer: 'New Transfer',
        cardQuickActions: 'Quick Actions',
        cardCurrencyRates: 'Currency Rates NBP',
        cardStockPrices: 'Stock Prices',
        
        // Forms
        fromAccount: 'From account:',
        toAccount: 'To account:',
        amount: 'Amount:',
        transferTitle: 'Title:',
        selectSourceAccount: 'Select source account',
        selectDestAccount: 'Select destination account',
        executeTransfer: 'Execute Transfer',
        deposit: 'Deposit',
        withdraw: 'Withdraw',
        selectAccount: 'Select account',
        
        // Table headers
        thName: 'Name',
        thType: 'Type',
        thPhone: 'Phone',
        thEmail: 'Email',
        thAccounts: 'Accounts',
        
        // Account types
        accountSavings: 'Savings',
        accountInvestment: 'Investment',
        accountCurrency: 'Currency',
        accountStandard: 'Standard',
        
        // Client types
        clientIndividual: 'Individual',
        clientCompany: 'Company',
        
        // Status
        statusActive: 'Active',
        statusInactive: 'Inactive',
        serverOnline: 'Server online',
        serverOffline: 'Server offline',
        serverChecking: 'Checking...',
        
        // Messages
        loading: 'Loading...',
        noData: 'No data',
        noBanks: 'No banks in the system',
        noClients: 'No clients',
        noAccounts: 'No accounts to display',
        noRatesData: 'No exchange rate data',
        fillAllFields: 'Fill all fields correctly',
        accountsMustDiffer: 'Accounts must be different',
        transferSuccess: 'Transfer completed successfully!',
        depositSuccess: 'Deposit completed successfully!',
        withdrawSuccess: 'Withdrawal completed successfully!',
        transferError: 'Transfer error',
        depositError: 'Deposit error',
        withdrawError: 'Withdrawal error',
        
        // Misc
        refresh: 'Refresh',
        clients: 'Clients',
        accounts: 'Accounts',
        assets: 'Assets',
        unknown: 'Unknown',
        bank: 'Bank',
        noAddress: 'No address',
        owner: 'Owner'
    },
    pl: {
        // Login screen
        loginTitle: 'BankSystem',
        loginSubtitle: 'Wybierz profil użytkownika',
        loginAdmin: 'Administrator',
        loginAdminDesc: 'Pełny dostęp do systemu',
        loginCompany: 'Firma',
        loginCompanyDesc: 'TechCorp Sp. z o.o.',
        loginClient: 'Klient',
        loginClientDesc: 'Jan Kowalski',
        loginFooter: 'Wersja demonstracyjna - bez autoryzacji',
        
        // Navigation
        navDashboard: 'Dashboard',
        navBanks: 'Banki',
        navClients: 'Klienci',
        navAccounts: 'Moje konta',
        navAllAccounts: 'Wszystkie konta',
        navTransfers: 'Przelewy',
        navMarket: 'Rynek',
        
        // Dashboard
        titleDashboard: 'Panel główny',
        titleBanks: 'Banki',
        titleClients: 'Klienci',
        titleAccounts: 'Konta',
        titleTransfers: 'Przelewy',
        titleMarket: 'Rynek',
        
        // Stats
        statBanks: 'Banków',
        statClients: 'Klientów',
        statAccounts: 'Kont',
        statMyAccounts: 'Moich kont',
        statBalance: 'Suma sald',
        statMyBalance: 'Moje środki',
        
        // Cards
        cardBanksOverview: 'Przegląd banków',
        cardMyAccounts: 'Moje konta',
        cardExchangeRates: 'Kursy walut',
        cardBanksList: 'Lista banków',
        cardClientsList: 'Lista klientów',
        cardAccountsList: 'Lista kont',
        cardNewTransfer: 'Nowy przelew',
        cardQuickActions: 'Szybkie operacje',
        cardCurrencyRates: 'Kursy walut NBP',
        cardStockPrices: 'Ceny akcji',
        
        // Forms
        fromAccount: 'Z konta:',
        toAccount: 'Na konto:',
        amount: 'Kwota:',
        transferTitle: 'Tytuł:',
        selectSourceAccount: 'Wybierz konto źródłowe',
        selectDestAccount: 'Wybierz konto docelowe',
        executeTransfer: 'Wykonaj przelew',
        deposit: 'Wpłata',
        withdraw: 'Wypłata',
        selectAccount: 'Wybierz konto',
        
        // Table headers
        thName: 'Nazwa',
        thType: 'Typ',
        thPhone: 'Telefon',
        thEmail: 'Email',
        thAccounts: 'Kont',
        
        // Account types
        accountSavings: 'Oszczędnościowe',
        accountInvestment: 'Inwestycyjne',
        accountCurrency: 'Walutowe',
        accountStandard: 'Standardowe',
        
        // Client types
        clientIndividual: 'Osoba',
        clientCompany: 'Firma',
        
        // Status
        statusActive: 'Aktywne',
        statusInactive: 'Nieaktywne',
        serverOnline: 'Serwer online',
        serverOffline: 'Serwer offline',
        serverChecking: 'Sprawdzanie...',
        
        // Messages
        loading: 'Ładowanie...',
        noData: 'Brak danych',
        noBanks: 'Brak banków w systemie',
        noClients: 'Brak klientów',
        noAccounts: 'Brak kont do wyświetlenia',
        noRatesData: 'Brak danych o kursach',
        fillAllFields: 'Wypełnij wszystkie pola poprawnie',
        accountsMustDiffer: 'Konta muszą być różne',
        transferSuccess: 'Przelew wykonany pomyślnie!',
        depositSuccess: 'Wpłata wykonana pomyślnie!',
        withdrawSuccess: 'Wypłata wykonana pomyślnie!',
        transferError: 'Błąd przelewu',
        depositError: 'Błąd wpłaty',
        withdrawError: 'Błąd wypłaty',
        
        // Misc
        refresh: 'Odśwież',
        clients: 'Klientów',
        accounts: 'Kont',
        assets: 'Aktywa',
        unknown: 'Nieznany',
        bank: 'Bank',
        noAddress: 'Brak adresu',
        owner: 'Właściciel'
    }
};

// Current language (default: English)
let currentLang = localStorage.getItem('bankSystemLang') || 'en';

// Get translation
function t(key) {
    return translations[currentLang]?.[key] || translations['en'][key] || key;
}

// Change language
function setLanguage(lang) {
    currentLang = lang;
    localStorage.setItem('bankSystemLang', lang);
    updateAllTranslations();
    
    // Update language selector
    const selector = document.getElementById('lang-selector');
    if (selector) selector.value = lang;
}

// Update all UI text
function updateAllTranslations() {
    // Login screen
    document.querySelector('.login-header h1').textContent = t('loginTitle');
    document.querySelector('.login-header p').textContent = t('loginSubtitle');
    document.querySelector('.login-footer small').textContent = t('loginFooter');
    
    const loginOptions = document.querySelectorAll('.login-option');
    if (loginOptions[0]) {
        loginOptions[0].querySelector('.login-role').textContent = t('loginAdmin');
        loginOptions[0].querySelector('.login-desc').textContent = t('loginAdminDesc');
    }
    if (loginOptions[1]) {
        loginOptions[1].querySelector('.login-role').textContent = t('loginCompany');
        loginOptions[1].querySelector('.login-desc').textContent = t('loginCompanyDesc');
    }
    if (loginOptions[2]) {
        loginOptions[2].querySelector('.login-role').textContent = t('loginClient');
        loginOptions[2].querySelector('.login-desc').textContent = t('loginClientDesc');
    }
    
    // Navigation (only update visible items)
    const navItems = document.querySelectorAll('.nav-item');
    navItems.forEach(item => {
        const view = item.dataset.view;
        const span = item.querySelector('span');
        if (!span) return;
        
        switch(view) {
            case 'dashboard': span.textContent = t('navDashboard'); break;
            case 'banks': span.textContent = t('navBanks'); break;
            case 'clients': span.textContent = t('navClients'); break;
            case 'accounts': 
                const role = state.currentUser?.role;
                span.textContent = role === 'admin' ? t('navAllAccounts') : t('navAccounts'); 
                break;
            case 'transfers': span.textContent = t('navTransfers'); break;
            case 'market': span.textContent = t('navMarket'); break;
        }
    });
    
    // Update current view title
    if (state.currentView) {
        const titleKey = 'title' + state.currentView.charAt(0).toUpperCase() + state.currentView.slice(1);
        const titleEl = document.getElementById('view-title');
        if (titleEl) titleEl.textContent = t(titleKey);
    }
    
    // Stats labels
    const role = state.currentUser?.role || 'admin';
    const accountsLabel = document.getElementById('stat-accounts-label');
    const balanceLabel = document.getElementById('stat-balance-label');
    
    if (role === 'admin') {
        if (accountsLabel) accountsLabel.textContent = t('statAccounts');
        if (balanceLabel) balanceLabel.textContent = t('statBalance');
    } else {
        if (accountsLabel) accountsLabel.textContent = t('statMyAccounts');
        if (balanceLabel) balanceLabel.textContent = t('statMyBalance');
    }
    
    // Card headers
    updateCardHeaders();
    
    // Form labels
    updateFormLabels();
    
    // Reload current view to update dynamic content
    if (state.currentUser) {
        loadViewData(state.currentView);
    }
}

function updateCardHeaders() {
    // Dashboard cards
    const dashboardTitle = document.getElementById('dashboard-main-title');
    if (dashboardTitle) {
        dashboardTitle.textContent = state.currentUser?.role === 'admin' ? t('cardBanksOverview') : t('cardMyAccounts');
    }
    
    // Exchange rates card - try different possible selectors
    document.querySelectorAll('.card-header h3').forEach(h3 => {
        const icon = h3.querySelector('i');
        if (!icon) return;
        
        if (icon.classList.contains('fa-chart-line') && h3.closest('.market-rates')) {
            const span = h3.querySelector('span') || h3.childNodes[h3.childNodes.length - 1];
            if (span && span.nodeType === 3) {
                h3.innerHTML = `<i class="fas fa-chart-line"></i> ${t('cardExchangeRates')}`;
            }
        }
    });
}

function updateFormLabels() {
    // Transfer form labels
    const labels = {
        'transfer-from': t('fromAccount'),
        'transfer-to': t('toAccount'),
        'transfer-amount': t('amount'),
        'transfer-title': t('transferTitle')
    };
    
    for (const [id, text] of Object.entries(labels)) {
        const input = document.getElementById(id);
        if (input) {
            const label = input.closest('.form-group')?.querySelector('label');
            if (label) label.textContent = text;
        }
    }
    
    // Quick actions titles
    document.querySelectorAll('.card-body h4').forEach(h4 => {
        if (h4.textContent.includes('Wpłata') || h4.textContent.includes('Deposit')) {
            h4.textContent = t('deposit');
        } else if (h4.textContent.includes('Wypłata') || h4.textContent.includes('Withdraw')) {
            h4.textContent = t('withdraw');
        }
    });
}

// ============================================
// State Management
// ============================================

const state = {
    currentUser: null,
    currentView: 'dashboard',
    banks: [],
    clients: [],
    accounts: [],
    rates: [],
    stocks: [],
    stockCurrency: 'PLN',
    lastRatesUpdate: null
};

// Demo users with specific client IDs matching backend data
const demoUsers = {
    admin: { 
        role: 'admin', 
        name: 'Administrator', 
        icon: 'fas fa-user-shield',
        clientId: null,  // Admin sees all
        clientName: null
    },
    company: { 
        role: 'company', 
        name: 'TechCorp Sp. z o.o.', 
        icon: 'fas fa-building',
        clientId: 2001,  // Matches backend TechCorp client ID
        clientName: 'TechCorp Sp. z o.o.'
    },
    client: { 
        role: 'client', 
        name: 'Jan Kowalski', 
        icon: 'fas fa-user',
        clientId: 1001,  // Matches backend Jan Kowalski client ID
        clientName: 'Jan Kowalski'
    }
};

// Role permissions
const rolePermissions = {
    admin: {
        canViewAllBanks: true,
        canViewAllClients: true,
        canViewAllAccounts: true,
        canTransferAnywhere: true,
        views: ['dashboard', 'banks', 'clients', 'accounts', 'transfers', 'market']
    },
    company: {
        canViewAllBanks: false,
        canViewAllClients: false,
        canViewAllAccounts: false,
        canTransferAnywhere: false,
        views: ['dashboard', 'accounts', 'transfers', 'market']
    },
    client: {
        canViewAllBanks: false,
        canViewAllClients: false,
        canViewAllAccounts: false,
        canTransferAnywhere: false,
        views: ['dashboard', 'accounts', 'transfers', 'market']
    }
};

// ============================================
// Login / Logout
// ============================================

function login(role) {
    state.currentUser = demoUsers[role];
    document.getElementById('login-screen').style.display = 'none';
    document.getElementById('app').style.display = 'flex';
    document.getElementById('current-user-name').textContent = state.currentUser.name;
    
    // Apply role-based UI restrictions
    applyRoleRestrictions();
    
    // Initialize application
    init();
}

function logout() {
    state.currentUser = null;
    state.accounts = [];
    state.clients = [];
    state.banks = [];
    document.getElementById('app').style.display = 'none';
    document.getElementById('login-screen').style.display = 'flex';
}

function applyRoleRestrictions() {
    const role = state.currentUser.role;
    const permissions = rolePermissions[role];
    
    // Show/hide navigation items based on role
    document.querySelectorAll('.nav-item').forEach(item => {
        const allowedRoles = item.dataset.roles?.split(',') || [];
        if (allowedRoles.includes(role)) {
            item.style.display = 'flex';
        } else {
            item.style.display = 'none';
        }
    });
    
    // Show/hide stat cards based on role
    document.querySelectorAll('.stat-card').forEach(card => {
        const allowedRoles = card.dataset.roles?.split(',') || [];
        if (allowedRoles.includes(role)) {
            card.style.display = 'flex';
        } else {
            card.style.display = 'none';
        }
    });
    
    // Update labels based on role
    const accountsLabel = document.getElementById('stat-accounts-label');
    const balanceLabel = document.getElementById('stat-balance-label');
    
    if (role === 'admin') {
        if (accountsLabel) accountsLabel.textContent = 'Kont';
        if (balanceLabel) balanceLabel.textContent = 'Suma sald';
    } else {
        if (accountsLabel) accountsLabel.textContent = 'Moich kont';
        if (balanceLabel) balanceLabel.textContent = 'Moje środki';
    }
    
    // Update "Konta" label in navigation based on role
    const accountsNav = document.querySelector('[data-view="accounts"]');
    if (accountsNav) {
        const span = accountsNav.querySelector('span');
        if (span) {
            span.textContent = role === 'admin' ? 'Wszystkie konta' : 'Moje konta';
        }
    }
}

// Helper to check if user can access a view
function canAccessView(viewName) {
    if (!state.currentUser) return false;
    const permissions = rolePermissions[state.currentUser.role];
    return permissions.views.includes(viewName);
}

// Helper to get user's accounts only
function getUserAccounts() {
    if (!state.currentUser) return [];
    if (state.currentUser.role === 'admin') {
        return state.accounts;
    }
    // Filter by client name matching
    return state.accounts.filter(acc => 
        acc.owner === state.currentUser.clientName ||
        acc.owner === state.currentUser.name
    );
}

// Helper to get user's clients (for admin only)
function getUserClients() {
    if (!state.currentUser) return [];
    if (state.currentUser.role === 'admin') {
        return state.clients;
    }
    return state.clients.filter(c => 
        c.name === state.currentUser.clientName ||
        c.name === state.currentUser.name
    );
}

// ============================================
// API Functions
// ============================================

async function fetchAPI(endpoint) {
    try {
        const response = await fetch(`/api/${endpoint}`);
        if (!response.ok) throw new Error(`HTTP ${response.status}`);
        return await response.json();
    } catch (error) {
        console.error(`Error fetching ${endpoint}:`, error);
        return null;
    }
}

async function postAPI(endpoint, data) {
    try {
        const response = await fetch(`/api/${endpoint}`, {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify(data)
        });
        return await response.json();
    } catch (error) {
        console.error(`Error posting to ${endpoint}:`, error);
        return { success: false, error: error.message };
    }
}

// ============================================
// NBP Live Exchange Rates
// ============================================

async function fetchNBPRates() {
    try {
        const response = await fetch('https://api.nbp.pl/api/exchangerates/tables/A/?format=json');
        if (!response.ok) throw new Error('NBP API error');
        const data = await response.json();
        
        if (data && data[0] && data[0].rates) {
            state.rates = data[0].rates;
            state.lastRatesUpdate = new Date();
            return true;
        }
    } catch (error) {
        console.error('Failed to fetch NBP rates:', error);
        // Use fallback rates
        state.rates = [
            { code: 'USD', currency: 'dolar amerykański', mid: 4.05 },
            { code: 'EUR', currency: 'euro', mid: 4.32 },
            { code: 'GBP', currency: 'funt szterling', mid: 5.10 },
            { code: 'CHF', currency: 'frank szwajcarski', mid: 4.52 }
        ];
    }
    return false;
}

function getRate(currencyCode) {
    if (currencyCode === 'PLN') return 1;
    const rate = state.rates.find(r => r.code === currencyCode);
    return rate ? rate.mid : 1;
}

function convertCurrency(amount, fromCurrency, toCurrency) {
    if (fromCurrency === toCurrency) return amount;
    
    const fromRate = getRate(fromCurrency);
    const toRate = getRate(toCurrency);
    
    // Convert to PLN first, then to target currency
    const inPLN = amount * fromRate;
    return inPLN / toRate;
}

// ============================================
// Phone Number Formatting
// ============================================

function formatPhone(phone) {
    if (!phone) return '';
    // Remove all non-digits
    const digits = phone.replace(/\D/g, '');
    
    // Handle Polish numbers
    let cleaned = digits;
    if (digits.startsWith('48') && digits.length > 9) {
        cleaned = digits.substring(2);
    } else if (digits.startsWith('0048')) {
        cleaned = digits.substring(4);
    }
    
    // Take last 9 digits if longer
    if (cleaned.length > 9) {
        cleaned = cleaned.slice(-9);
    }
    
    // Pad with zeros if shorter
    cleaned = cleaned.padStart(9, '0');
    
    // Format as +48-xxx-xxx-xxx
    return `+48-${cleaned.slice(0,3)}-${cleaned.slice(3,6)}-${cleaned.slice(6,9)}`;
}

// ============================================
// Navigation
// ============================================

function navigate(viewName) {
    state.currentView = viewName;
    
    // Update nav items
    document.querySelectorAll('.nav-item').forEach(item => {
        item.classList.toggle('active', item.dataset.view === viewName);
    });
    
    // Update views
    document.querySelectorAll('.view').forEach(view => {
        view.classList.toggle('active', view.id === `${viewName}-view`);
    });
    
    // Update header title
    const titles = {
        dashboard: 'Panel główny',
        banks: 'Banki',
        clients: 'Klienci',
        accounts: 'Konta',
        transfers: 'Przelewy',
        market: 'Rynek'
    };
    document.getElementById('view-title').textContent = titles[viewName] || 'Panel główny';
    
    // Load view data
    loadViewData(viewName);
}

async function loadViewData(viewName) {
    switch (viewName) {
        case 'dashboard':
            await loadDashboard();
            break;
        case 'banks':
            await loadBanks();
            break;
        case 'clients':
            await loadClients();
            break;
        case 'accounts':
            await loadAccounts();
            break;
        case 'transfers':
            await loadTransfers();
            break;
        case 'market':
            await loadMarket();
            break;
    }
}

// ============================================
// Dashboard View
// ============================================

async function loadDashboard() {
    const [banks, clients, accounts, summary] = await Promise.all([
        fetchAPI('banks'),
        fetchAPI('clients'),
        fetchAPI('accounts'),
        fetchAPI('summary')
    ]);
    
    state.banks = banks || [];
    state.clients = clients || [];
    state.accounts = accounts || [];
    
    const role = state.currentUser?.role || 'client';
    const permissions = rolePermissions[role];
    
    // Get filtered data based on role
    const userAccounts = getUserAccounts();
    const userClients = getUserClients();
    
    // Update stats based on role
    const statBanks = document.getElementById('stat-banks');
    const statClients = document.getElementById('stat-clients');
    const statAccounts = document.getElementById('stat-accounts');
    const statBalance = document.getElementById('stat-balance');
    
    if (role === 'admin') {
        // Admin sees everything
        statBanks.textContent = state.banks.length;
        statClients.textContent = state.clients.length;
        statAccounts.textContent = state.accounts.length;
        const totalBalance = state.accounts.reduce((sum, acc) => sum + (acc.balance || 0), 0);
        statBalance.textContent = formatMoney(totalBalance);
    } else {
        // Non-admin sees only their data
        statBanks.textContent = '-'; // Not relevant
        statClients.textContent = '1'; // Just themselves
        statAccounts.textContent = userAccounts.length;
        const userBalance = userAccounts.reduce((sum, acc) => sum + (acc.balance || 0), 0);
        statBalance.textContent = formatMoney(userBalance);
    }
    
    // Render appropriate content
    renderDashboardContent(role);
    
    // Render exchange rates (same for everyone)
    renderExchangeRates();
}

function renderDashboardContent(role) {
    const container = document.getElementById('recent-banks');
    const titleEl = document.getElementById('dashboard-main-title');
    const headerIcon = document.querySelector('#dashboard-main-header h3 i');
    
    if (!container) return;
    
    if (role === 'admin') {
        // Admin sees banks overview
        if (titleEl) titleEl.textContent = 'Przegląd banków';
        if (headerIcon) headerIcon.className = 'fas fa-building';
        renderRecentBanks();
    } else {
        // Users see their accounts overview
        if (titleEl) titleEl.textContent = 'Moje konta';
        if (headerIcon) headerIcon.className = 'fas fa-wallet';
        renderUserAccountsSummary();
    }
}

function renderUserAccountsSummary() {
    const container = document.getElementById('recent-banks');
    if (!container) return;
    
    const userAccounts = getUserAccounts();
    
    if (userAccounts.length === 0) {
        container.innerHTML = `<p class="text-muted">${t('noAccounts')}</p>`;
        return;
    }
    
    const html = userAccounts.map(account => `
        <div class="account-card" style="margin-bottom: 12px;">
            <div class="account-header">
                <span class="account-type ${account.type || 'savings'}">
                    <i class="fas fa-${getAccountIcon(account.type)}"></i>
                    ${getAccountTypeName(account.type)}
                </span>
                <span class="badge ${account.isActive ? 'success' : 'warning'}">
                    ${account.isActive ? t('statusActive') : t('statusInactive')}
                </span>
            </div>
            <div class="account-balance">
                ${formatMoney(account.balance, account.currency || 'PLN')}
            </div>
            <div class="account-iban" style="font-size: 0.75rem; color: var(--secondary);">
                ${account.iban || account.accountNumber}
            </div>
        </div>
    `).join('');
    
    container.innerHTML = html;
}

function renderRecentBanks() {
    const container = document.getElementById('recent-banks');
    if (!container) return;
    
    const html = state.banks.slice(0, 3).map(bank => `
        <div class="bank-card">
            <h4><i class="fas fa-university"></i> ${bank.name}</h4>
            <div class="bank-details">${bank.address || 'Brak adresu'}</div>
            <div class="bank-stats">
                <div class="bank-stat">
                    <span class="bank-stat-value">${bank.clientCount || 0}</span>
                    <span class="bank-stat-label">Klientów</span>
                </div>
                <div class="bank-stat">
                    <span class="bank-stat-value">${bank.accountCount || 0}</span>
                    <span class="bank-stat-label">Kont</span>
                </div>
            </div>
        </div>
    `).join('');
    
    container.innerHTML = html || `<p class="text-muted">${t('noData')}</p>`;
}

function renderExchangeRates() {
    const container = document.getElementById('exchange-rates');
    if (!container) return;
    
    const mainCurrencies = ['USD', 'EUR', 'GBP', 'CHF'];
    const flags = { USD: '🇺🇸', EUR: '🇪🇺', GBP: '🇬🇧', CHF: '🇨🇭' };
    
    const html = mainCurrencies.map(code => {
        const rate = state.rates.find(r => r.code === code);
        if (!rate) return '';
        
        return `
            <div class="rate-item">
                <div class="rate-currency">
                    <span class="currency-flag">${flags[code]}</span>
                    <div>
                        <strong>${code}</strong>
                        <div class="text-muted" style="font-size: 0.75rem">${rate.currency}</div>
                    </div>
                </div>
                <span class="rate-value">${rate.mid.toFixed(4)} PLN</span>
            </div>
        `;
    }).join('');
    
    container.innerHTML = html || `<p class="text-muted">${t('noRatesData')}</p>`;
}

// ============================================
// Banks View
// ============================================

async function loadBanks() {
    const banks = await fetchAPI('banks');
    state.banks = banks || [];
    
    const container = document.getElementById('banks-list');
    if (!container) return;
    
    const html = state.banks.map(bank => `
        <div class="bank-card">
            <h4><i class="fas fa-university"></i> ${bank.name}</h4>
            <div class="bank-details">
                <div><i class="fas fa-map-marker-alt"></i> ${bank.address || t('noAddress')}</div>
                <div><i class="fas fa-phone"></i> ${formatPhone(bank.phone)}</div>
            </div>
            <div class="bank-stats">
                <div class="bank-stat">
                    <span class="bank-stat-value">${bank.clientCount || 0}</span>
                    <span class="bank-stat-label">${t('clients')}</span>
                </div>
                <div class="bank-stat">
                    <span class="bank-stat-value">${bank.accountCount || 0}</span>
                    <span class="bank-stat-label">${t('accounts')}</span>
                </div>
                <div class="bank-stat">
                    <span class="bank-stat-value">${formatMoney(bank.totalBalance || 0)}</span>
                    <span class="bank-stat-label">${t('assets')}</span>
                </div>
            </div>
        </div>
    `).join('');
    
    container.innerHTML = html || `<p class="text-muted">${t('noBanks')}</p>`;
}

// ============================================
// Clients View
// ============================================

async function loadClients() {
    const clients = await fetchAPI('clients');
    state.clients = clients || [];
    
    const container = document.getElementById('clients-table-body');
    if (!container) return;
    
    const html = state.clients.map(client => `
        <tr>
            <td>
                <strong>${client.name || client.firstName + ' ' + client.lastName}</strong>
            </td>
            <td>
                <span class="client-type ${client.type === 'company' ? 'company' : 'individual'}">
                    <i class="fas fa-${client.type === 'company' ? 'building' : 'user'}"></i>
                    ${client.type === 'company' ? t('clientCompany') : t('clientIndividual')}
                </span>
            </td>
            <td>${formatPhone(client.phone)}</td>
            <td>${client.email || '-'}</td>
            <td>${client.accountCount || 0}</td>
        </tr>
    `).join('');
    
    container.innerHTML = html || `<tr><td colspan="5" class="text-muted">${t('noClients')}</td></tr>`;
}

// ============================================
// Accounts View
// ============================================

async function loadAccounts() {
    const accounts = await fetchAPI('accounts');
    state.accounts = accounts || [];
    
    const container = document.getElementById('accounts-list');
    if (!container) return;
    
    // Filter accounts based on role
    const displayAccounts = getUserAccounts();
    const role = state.currentUser?.role || 'client';
    
    if (displayAccounts.length === 0) {
        container.innerHTML = `<p class="text-muted">${t('noAccounts')}</p>`;
        return;
    }
    
    const html = displayAccounts.map(account => `
        <div class="account-card">
            <div class="account-header">
                <span class="account-type ${account.type || 'savings'}">
                    <i class="fas fa-${getAccountIcon(account.type)}"></i>
                    ${getAccountTypeName(account.type)}
                </span>
                <span class="badge ${account.isActive ? 'success' : 'warning'}">
                    ${account.isActive ? t('statusActive') : t('statusInactive')}
                </span>
            </div>
            <div class="account-balance">
                ${formatMoney(account.balance, account.currency || 'PLN')}
            </div>
            <div class="account-iban">${account.iban || account.accountNumber}</div>
            <div class="account-meta">
                <span><i class="fas fa-user"></i> ${account.owner || t('unknown')}</span>
                <span><i class="fas fa-university"></i> ${account.bank || t('bank')}</span>
            </div>
        </div>
    `).join('');
    
    container.innerHTML = html;
}

function getAccountIcon(type) {
    const icons = {
        savings: 'piggy-bank',
        investment: 'chart-line',
        currency: 'globe'
    };
    return icons[type] || 'wallet';
}

function getAccountTypeName(type) {
    const names = {
        savings: t('accountSavings'),
        investment: t('accountInvestment'),
        currency: t('accountCurrency')
    };
    return names[type] || t('accountStandard');
}

// ============================================
// Transfers View
// ============================================

async function loadTransfers() {
    const accounts = await fetchAPI('accounts');
    state.accounts = accounts || [];
    
    populateAccountSelects();
}

function populateAccountSelects() {
    const fromSelect = document.getElementById('transfer-from');
    const toSelect = document.getElementById('transfer-to');
    const depositAccount = document.getElementById('deposit-account');
    const withdrawAccount = document.getElementById('withdraw-account');
    
    const role = state.currentUser?.role || 'client';
    const userAccounts = getUserAccounts();
    const allAccounts = state.accounts;
    
    // User's accounts for "from" select (can only transfer FROM own accounts)
    const fromOptions = userAccounts.map(acc => 
        `<option value="${acc.iban || acc.accountNumber}">${acc.owner || 'Konto'} - ${formatMoney(acc.balance)} (${acc.currency || 'PLN'})</option>`
    ).join('');
    
    // For "to" select: admin can transfer anywhere, others can transfer to any account
    const toOptions = allAccounts.map(acc => 
        `<option value="${acc.iban || acc.accountNumber}">${acc.owner || 'Konto'} - ${acc.bank || 'Bank'}</option>`
    ).join('');
    
    // Deposit/withdraw only for own accounts
    const ownOptions = userAccounts.map(acc => 
        `<option value="${acc.iban || acc.accountNumber}">${getAccountTypeName(acc.type)} - ${formatMoney(acc.balance)} (${acc.currency || 'PLN'})</option>`
    ).join('');
    
    if (fromSelect) fromSelect.innerHTML = `<option value="">${t('selectSourceAccount')}</option>` + fromOptions;
    if (toSelect) toSelect.innerHTML = `<option value="">${t('selectDestAccount')}</option>` + toOptions;
    if (depositAccount) depositAccount.innerHTML = `<option value="">${t('selectAccount')}</option>` + ownOptions;
    if (withdrawAccount) withdrawAccount.innerHTML = `<option value="">${t('selectAccount')}</option>` + ownOptions;
}

async function executeTransfer() {
    const from = document.getElementById('transfer-from').value;
    const to = document.getElementById('transfer-to').value;
    const amount = parseFloat(document.getElementById('transfer-amount').value);
    const title = document.getElementById('transfer-title').value;
    
    if (!from || !to || !amount || amount <= 0) {
        showToast(t('fillAllFields'), 'error');
        return;
    }
    
    if (from === to) {
        showToast(t('accountsMustDiffer'), 'error');
        return;
    }
    
    const result = await postAPI('transfer', { from, to, amount, title });
    
    if (result.success) {
        showToast(t('transferSuccess'), 'success');
        document.getElementById('transfer-form').reset();
        loadTransfers();
    } else {
        showToast(result.error || t('transferError'), 'error');
    }
}

async function executeDeposit() {
    const account = document.getElementById('deposit-account').value;
    const amount = parseFloat(document.getElementById('deposit-amount').value);
    
    if (!account || !amount || amount <= 0) {
        showToast(t('fillAllFields'), 'error');
        return;
    }
    
    const result = await postAPI('deposit', { account, amount });
    
    if (result.success) {
        showToast(t('depositSuccess'), 'success');
        document.getElementById('deposit-form').reset();
        loadTransfers();
    } else {
        showToast(result.error || t('depositError'), 'error');
    }
}

async function executeWithdraw() {
    const account = document.getElementById('withdraw-account').value;
    const amount = parseFloat(document.getElementById('withdraw-amount').value);
    
    if (!account || !amount || amount <= 0) {
        showToast(t('fillAllFields'), 'error');
        return;
    }
    
    const result = await postAPI('withdraw', { account, amount });
    
    if (result.success) {
        showToast(t('withdrawSuccess'), 'success');
        document.getElementById('withdraw-form').reset();
        loadTransfers();
    } else {
        showToast(result.error || t('withdrawError'), 'error');
    }
}

// ============================================
// Market View
// ============================================

async function loadMarket() {
    await fetchNBPRates();
    const market = await fetchAPI('market');
    
    // Convert stocks object to array if needed
    if (market?.stocks && typeof market.stocks === 'object' && !Array.isArray(market.stocks)) {
        state.stocks = Object.entries(market.stocks).map(([ticker, price]) => ({
            ticker,
            name: getStockName(ticker),
            price,
            currency: 'USD',
            change: (Math.random() * 4 - 2).toFixed(1) // simulated change
        }));
    } else {
        state.stocks = getDefaultStocks();
    }
    
    renderMarketRates();
    renderStocks();
}

function getStockName(ticker) {
    const names = {
        'AAPL': 'Apple Inc.',
        'GOOGL': 'Alphabet Inc.',
        'MSFT': 'Microsoft Corp.',
        'AMZN': 'Amazon.com',
        'TSLA': 'Tesla Inc.',
        'META': 'Meta Platforms'
    };
    return names[ticker] || ticker;
}

function getDefaultStocks() {
    return [
        { ticker: 'AAPL', name: 'Apple Inc.', price: 178.50, currency: 'USD', change: 1.2 },
        { ticker: 'GOOGL', name: 'Alphabet Inc.', price: 141.80, currency: 'USD', change: -0.5 },
        { ticker: 'MSFT', name: 'Microsoft Corp.', price: 378.20, currency: 'USD', change: 0.8 },
        { ticker: 'AMZN', name: 'Amazon.com', price: 178.90, currency: 'USD', change: 2.1 },
        { ticker: 'TSLA', name: 'Tesla Inc.', price: 248.50, currency: 'USD', change: -1.3 }
    ];
}

function renderMarketRates() {
    const container = document.getElementById('market-rates');
    if (!container) return;
    
    const flags = { 
        USD: '🇺🇸', EUR: '🇪🇺', GBP: '🇬🇧', CHF: '🇨🇭', 
        JPY: '🇯🇵', CAD: '🇨🇦', AUD: '🇦🇺', SEK: '🇸🇪',
        NOK: '🇳🇴', DKK: '🇩🇰', CZK: '🇨🇿', HUF: '🇭🇺'
    };
    
    const mainCurrencies = ['USD', 'EUR', 'GBP', 'CHF', 'JPY', 'CAD', 'AUD', 'CZK'];
    
    const html = mainCurrencies.map(code => {
        const rate = state.rates.find(r => r.code === code);
        if (!rate) return '';
        
        return `
            <div class="rate-item">
                <div class="rate-currency">
                    <span class="currency-flag">${flags[code] || '🏳️'}</span>
                    <div>
                        <strong>${code}</strong>
                        <div class="text-muted" style="font-size: 0.75rem">${rate.currency}</div>
                    </div>
                </div>
                <span class="rate-value">${rate.mid.toFixed(4)} PLN</span>
            </div>
        `;
    }).join('');
    
    container.innerHTML = html || '<p class="text-muted">Brak danych</p>';
}

function renderStocks() {
    const container = document.getElementById('stocks-list');
    if (!container) return;
    
    const targetCurrency = state.stockCurrency;
    const currencySymbols = { PLN: 'zł', USD: '$', EUR: '€', GBP: '£' };
    
    const html = state.stocks.map(stock => {
        const convertedPrice = convertCurrency(stock.price, stock.currency, targetCurrency);
        const symbol = currencySymbols[targetCurrency] || targetCurrency;
        const changeClass = stock.change >= 0 ? 'color: var(--success)' : 'color: var(--danger)';
        const changeIcon = stock.change >= 0 ? 'fa-arrow-up' : 'fa-arrow-down';
        
        return `
            <div class="stock-item">
                <div>
                    <span class="stock-ticker">${stock.ticker}</span>
                    <div class="text-muted" style="font-size: 0.75rem">${stock.name}</div>
                </div>
                <div style="text-align: right">
                    <span class="stock-price">${convertedPrice.toFixed(2)} ${symbol}</span>
                    <div style="${changeClass}; font-size: 0.8rem">
                        <i class="fas ${changeIcon}"></i> ${Math.abs(stock.change).toFixed(1)}%
                    </div>
                </div>
            </div>
        `;
    }).join('');
    
    container.innerHTML = html || '<p class="text-muted">Brak danych o akcjach</p>';
}

function changeStockCurrency(currency) {
    state.stockCurrency = currency;
    renderStocks();
}

// ============================================
// Utilities
// ============================================

function formatMoney(amount, currency = 'PLN') {
    const symbols = { PLN: 'zł', USD: '$', EUR: '€', GBP: '£' };
    const symbol = symbols[currency] || currency;
    return `${parseFloat(amount || 0).toLocaleString('pl-PL', { minimumFractionDigits: 2, maximumFractionDigits: 2 })} ${symbol}`;
}

function showToast(message, type = 'info') {
    const toast = document.getElementById('toast');
    if (!toast) return;
    
    toast.textContent = message;
    toast.className = `toast ${type}`;
    toast.classList.add('show');
    
    setTimeout(() => toast.classList.remove('show'), 3000);
}

// ============================================
// Server Status Check
// ============================================

async function checkServerStatus() {
    try {
        const response = await fetch('/api/banks', { method: 'HEAD' });
        const dot = document.getElementById('server-status-dot');
        const text = document.getElementById('server-status-text');
        
        if (response.ok) {
            if (dot) dot.classList.add('online');
            if (text) text.textContent = t('serverOnline');
        }
    } catch {
        const dot = document.getElementById('server-status-dot');
        const text = document.getElementById('server-status-text');
        if (dot) dot.classList.remove('online');
        if (text) text.textContent = t('serverOffline');
    }
}

// ============================================
// Initialization
// ============================================

async function init() {
    // Fetch NBP rates first
    await fetchNBPRates();
    
    // Check server status
    checkServerStatus();
    
    // Setup navigation
    document.querySelectorAll('.nav-item').forEach(item => {
        item.addEventListener('click', (e) => {
            e.preventDefault();
            navigate(item.dataset.view);
        });
    });
    
    // Setup stock currency selector
    const currencySelect = document.getElementById('stock-currency');
    if (currencySelect) {
        currencySelect.addEventListener('change', (e) => {
            changeStockCurrency(e.target.value);
        });
    }
    
    // Sync language selector
    const langSelector = document.getElementById('lang-selector');
    if (langSelector) langSelector.value = currentLang;
    
    // Update translations for current language
    updateAllTranslations();
    
    // Load initial view
    navigate('dashboard');
    
    // Refresh rates every 5 minutes
    setInterval(fetchNBPRates, 5 * 60 * 1000);
}

// Wait for DOM
document.addEventListener('DOMContentLoaded', () => {
    // Initialize language from localStorage
    const savedLang = localStorage.getItem('bankSystemLang') || 'en';
    currentLang = savedLang;
    
    // Set both language selectors
    const loginSelector = document.getElementById('lang-selector-login');
    const appSelector = document.getElementById('lang-selector');
    if (loginSelector) loginSelector.value = currentLang;
    if (appSelector) appSelector.value = currentLang;
    
    // Apply initial translations to login screen
    updateAllTranslations();
    
    // Check if already logged in (for demo purposes, start at login)
    document.getElementById('app').style.display = 'none';
    document.getElementById('login-screen').style.display = 'flex';
});
