$('body').click(function(e) {
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
})

function clickCheck(xPoint, yPoint) {
    //ip1B1
    if ((xPoint < 0.5)) {
        window.location.href = 'staff.html';
    }

    if ((xPoint > 0.5)) {
        window.location.href = 'shop.html';
    }
}