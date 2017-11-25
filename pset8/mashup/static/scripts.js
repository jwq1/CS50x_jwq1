// Google Map
var map;

// markers for map
var markers = [];

// marker labels
var labels = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ';
var labelIndex = 0;

// count which marker we are on
var markersIndex = 0;

// info window
var info = new google.maps.InfoWindow();

// info's content
var infoWindowContent = [];


// execute when the DOM is fully loaded
$(function() {

    // styles for map
    var styles = [

        // hide Google's labels
        {
            featureType: "all",
            elementType: "labels",
            stylers: [
                {visibility: "off"}
            ]
        },

        // hide roads
        {
            featureType: "road",
            elementType: "geometry",
            stylers: [
                {visibility: "off"}
            ]
        }

    ];

    // Make a variable for place
    map_placement_LatLng = {lat: 42.3770, lng: -71.1256}

    // options for map
    var options = {
        center: map_placement_LatLng, // Cambridge, Massachusetts
        disableDefaultUI: true,
        mapTypeId: google.maps.MapTypeId.ROADMAP,
        maxZoom: 14,
        panControl: true,
        styles: styles,
        zoom: 13,
        zoomControl: true
    };

    // get DOM node in which map will be instantiated
    var canvas = $("#map-canvas").get(0);

    // instantiate map
    map = new google.maps.Map(canvas, options);

    // configure UI once Google Map is idle (i.e., loaded)
    google.maps.event.addListenerOnce(map, "idle", configure);


});

/**
 * Adds marker for place to map.
 */
function addMarker(place)
{

    // get list of articles
    var parameters = {
        geo: place.postal_code

    };

    function getArticles(parameters, callback) {
        $.getJSON(Flask.url_for("articles"), parameters)
        .done(function(data, textStatus, jqXHR) {

            // Create div for info window content
            var contentString = '<div>'
            // create list of articles
            contentString += '<ul>';
            // loop through articles
            $.each(data, function (index, object) {
                // only open 5 articles
                if (index < 5) {
                    $.each(data[index], function (key, value)  {
                        if (key == "link") {
                            contentString += '<li><a href=' + value + '>';
                        } else if (key == "title") {
                            contentString += value + '</a></li>';
                        }
                    });
                } else {
                    // exit .each loop
                    return false;
                }
            });
            contentString += '</ul></div>';

            // When info is ready, set info window content with contentString.
            callback(contentString);

            // DELETE: Irrelevant, to be deleted.
            infoWindowContent.push(contentString);


        })
        .fail(function(jqXHR, textStatus, errorThrown) {

            // log error to browser's console
            console.log(errorThrown.toString());
        });
    }



    // Parse our each object's latitude and longitude.
    position_LatLng = {lat: parseFloat(place.latitude), lng: parseFloat(place.longitude)}

    // Create a new marker
    var marker = new google.maps.Marker({
      position: position_LatLng,
      map: map,
      title: String(place.place_name),
      label: String(place.place_name),
      icon: {
          url: 'https://maps.gstatic.com/mapfiles/api-3/images/spotlight-poi-dotless_hdpi.png',
          labelOrigin: new google.maps.Point(21,95),
          // This marker is 20 pixels wide by 32 pixels high.
          size: new google.maps.Size(44, 88),
          // The origin for this image is (0, 0).
          origin: new google.maps.Point(0, 0),
          // The anchor for this image is the base of the flagpole at (0, 32).
          anchor: new google.maps.Point(22, 79)
      }
    });

    // add our marker to the array of markers
    markers.push(marker);

    // Open info window when marker is clicked
    marker.addListener('click', function() {

        // When loading, show loading gif
        info.setContent('<div><img alt=\'loading\' src=\'/static/ajax-loader.gif\'/></div>');



        // When article content is ready, then add it to the info window.
        getArticles(parameters, function(content) {
            // if no articles were returned in the data, then tell user.
            if (typeof(content) == "undefined") {
                info.setContent('no articles for this location');
            } else {
                info.setContent(content);
            }

        });

        // open info window
        info.open(map, marker);

    });

    // count which marker we are on
    markersIndex += 1;

}

/**
 * Configures application.
 */
function configure()
{
    // update UI after map has been dragged
    google.maps.event.addListener(map, "dragend", function() {

        // if info window isn't open
        if (!info.getMap || !info.getMap())
        {
            update();
        }
    });

    // update UI after zoom level changes
    google.maps.event.addListener(map, "zoom_changed", function() {
        update();
    });

    // configure typeahead
    $("#q").typeahead({
        highlight: false,
        minLength: 1
    },
    {
        // Data set(s) compose the typeahead component
        display: function(suggestion) { return null; },
        limit: 10,
        source: search,
        templates: {
            // suggestion, is used to render a suggestion.
            // It has to be a precompiled template.
            // Defaults to the value of "display"
            suggestion: Handlebars.compile(
                "<div>" +
                "{{place_name}}, {{admin_name1}}, {{postal_code}}" +
                "</div>"
            )
        }
    });

    // re-center map after place is selected from drop-down
    $("#q").on("typeahead:selected", function(eventObject, suggestion, name) {

        // set map's center
        map.setCenter({lat: parseFloat(suggestion.latitude), lng: parseFloat(suggestion.longitude)});

        // update UI
        update();
    });

    // hide info window when text box has focus
    $("#q").focus(function(eventData) {
        info.close();
    });

    // re-enable ctrl- and right-clicking (and thus Inspect Element) on Google Map
    document.addEventListener("contextmenu", function(event) {
        event.returnValue = true;
        event.stopPropagation && event.stopPropagation();
        event.cancelBubble && event.cancelBubble();
    }, true);

    // update UI
    update();

    // give focus to text box
    $("#q").focus();
}

/**
 * Removes markers from map.
 */
function removeMarkers()
{
    // Remove every marker on the map
    for (var i = 0; i < markers.length; i++) {
        markers[i].setMap(null);
    }

    // Reset the array of markers
    markers = [];

    // reset marker index
    markersIndex = 0;

    // reset info window content array
    infoWindowContent = [];

}

/**
 * Searches database for typeahead's suggestions.
 */
function search(query, syncResults, asyncResults)
{
    // get places matching query (asynchronously)
    var parameters = {
        q: query
    };
    $.getJSON(Flask.url_for("search"), parameters)
    .done(function(data, textStatus, jqXHR) {

        // call typeahead's callback with search results (i.e., places)
        asyncResults(data);
    })
    .fail(function(jqXHR, textStatus, errorThrown) {

        // log error to browser's console
        console.log(errorThrown.toString());

        // call typeahead's callback with no results
        asyncResults([]);
    });
}

/**
 * Shows info window at marker with content.
 */
function showInfo(marker, content)
{
    // This is now handled in the addMarker function
    // Code kept for CS50 submission

    // start div
    var div = "<div id='info'>";
    if (typeof(content) == "undefined")
    {
        // http://www.ajaxload.info/
        div += "<img alt='loading' src='/static/ajax-loader.gif'/>";
    }
    else
    {
        div += content;
    }

    // end div
    div += "</div>";

    // set info window's content
    info.setContent(div);


    // // open info window (if not already open)
    // info.open(map, marker);

}

/**
 * Updates UI's markers.
 */
function update()
{
    // reset label index for new markers
    labelIndex = 0;

    // get map's bounds
    var bounds = map.getBounds();
    var ne = bounds.getNorthEast();
    var sw = bounds.getSouthWest();

    // get places within bounds (asynchronously)
    var parameters = {
        ne: ne.lat() + "," + ne.lng(),
        q: $("#q").val(),
        sw: sw.lat() + "," + sw.lng()
    };
    $.getJSON(Flask.url_for("update"), parameters)
    .done(function(data, textStatus, jqXHR) {

       // remove old markers from map
       removeMarkers();

       // add new markers to map
       for (var i = 0; i < data.length; i++)
       {
           addMarker(data[i]);
       }
    })
    .fail(function(jqXHR, textStatus, errorThrown) {

        // log error to browser's console
        console.log(errorThrown.toString());
    });
};
