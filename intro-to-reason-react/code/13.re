switch ((route, isLoggedIn, isAdmin)) {
| (Home, _, _) => <HomePage />
| (Login, false, _) => <LoginPage />
| (Login, true, _) => 
    changeRoute(NewsFeed);
    <NewsFeedPage />;
| (NewsFeed, false, false) => 
    changeRoute(Home);
    <HomePage />;
| (NewsFeed, true, false) => <NewsFeedPage />
| (NewsFeed, true, true) => <AdminNewsFeedPage />
}