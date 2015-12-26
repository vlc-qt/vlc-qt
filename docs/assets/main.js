$(document).ready(function() {
  // Variables
  var body = $('body'),
    win = $(window);

  function sidebarResize() {
    if ($(window).width() < 768) {
      $('.sidebar-offcanvas').addClass('anim');
    } else {
      $('.sidebar-offcanvas').removeClass('anim');
      $('.offcanvas').removeClass('active');
    }
  };

  function init() {
    $('[data-toggle=offcanvas]').click(function() {
      $('.offcanvas').toggleClass('active');
    });

    sidebarResize();
    $(window).resize(sidebarResize);

    searchBox.OnSearchSelectShow = function() {
      var searchSelectWindow = this.DOMSearchSelectWindow();
      var searchField = this.DOMSearchSelect();

      if (this.insideFrame) {
        var top = getYPos(searchField);

        // show search selection popup
        searchSelectWindow.style.display = 'block';
        searchSelectWindow.style.top = top + 'px';
      } else {
        var top = getYPos(searchField);

        // show search selection popup
        searchSelectWindow.style.display = 'block';
        searchSelectWindow.style.top = top + 'px';
      }

      // stop selection hide timer
      if (this.hideTimeout) {
        clearTimeout(this.hideTimeout);
        this.hideTimeout = 0;
      }
      return false; // to avoid "image drag" default event
    };

    searchBox.Search = function() {
      this.keyTimeout = 0;

      // strip leading whitespace
      var searchValue = this.DOMSearchField().value.replace(/^ +/, "");

      var code = searchValue.toLowerCase().charCodeAt(0);
      var idxChar = searchValue.substr(0, 1).toLowerCase();
      if (0xD800 <= code && code <= 0xDBFF && searchValue > 1) // surrogate pair
      {
        idxChar = searchValue.substr(0, 2);
      }

      var resultsPage;
      var resultsPageWithSearch;
      var hasResultsPage;

      var idx = indexSectionsWithContent[this.searchIndex].indexOf(idxChar);
      if (idx != -1) {
        var hexCode = idx.toString(16);
        resultsPage = this.resultsPath + '/' + indexSectionNames[this.searchIndex] + '_' + hexCode + '.html';
        resultsPageWithSearch = resultsPage + '?' + escape(searchValue);
        hasResultsPage = true;
      } else // nothing available for this search term
      {
        resultsPage = this.resultsPath + '/nomatches.html';
        resultsPageWithSearch = resultsPage;
        hasResultsPage = false;
      }

      window.frames.MSearchResults.location = resultsPageWithSearch;

      var domPopupSearchResultsWindow = this.DOMPopupSearchResultsWindow();

      if (domPopupSearchResultsWindow.style.display != 'block') {
        var domSearchBox = this.DOMSearchBox();
        this.DOMSearchClose().style.display = 'inline';
        if (this.insideFrame) {
          var domPopupSearchResults = this.DOMPopupSearchResults();
          domPopupSearchResultsWindow.style.position = 'relative';
          domPopupSearchResultsWindow.style.display = 'block';
          var width = document.body.clientWidth - 8; // the -8 is for IE :-(
          domPopupSearchResultsWindow.style.width = width + 'px';
          domPopupSearchResults.style.width = width + 'px';
        } else {
          var domPopupSearchResults = this.DOMPopupSearchResults();
          var top = getYPos(domSearchBox) + 10;
          domPopupSearchResultsWindow.style.display = 'block';
          domPopupSearchResultsWindow.style.top = top + 'px';
        }
      }

      this.lastSearchValue = searchValue;
      this.lastResultsPage = resultsPage;
    };
  }

  init();
});