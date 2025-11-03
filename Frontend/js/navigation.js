$(document).ready(function() {
    // Navigation click handler
    $('body').click(function(e) {
        // Only handle clicks if they're not on interactive elements
        if ($(e.target).is('button, a, input, select, textarea')) {
            return;
        }

        var x, y, width, height;
        x = e.pageX;
        y = e.pageY;
        width = $('body').width();
        height = $('body').height();
        xPoint = x / width;
        yPoint = y / height;

        console.log(x + "+" + y);
        console.log(width + " by " + height);
        console.log("Location: " + xPoint + " " + yPoint);

        clickCheck(xPoint, yPoint);
    });
});

function clickCheck(xPoint, yPoint) {
    // Navigate to staff page if clicked on left side
    if (xPoint < 0.5) {
        window.location.href = 'staff.html';
    }
    // Navigate to shop page if clicked on right side
    else if (xPoint > 0.5) {
        window.location.href = 'shop.html';
    }
}