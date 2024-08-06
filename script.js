
document.addEventListener('DOMContentLoaded', function() {
    const mapElement = document.getElementById('floridaMap');
    const counties = mapElement.querySelectorAll('path');

    function setColor(countyId, color) {
        const county = document.getElementById(countyId);
        if (county) {
            county.style.fill = color;
        }
    }

    const countyColors = {
        'Duval': 'red'
    };

    Object.keys(countyColors).forEach(countyId => {
        setColor(countyId, countyColors[countyId]);
    });

    counties.forEach(county => {
        county.addEventListener('click', function() {
            alert('You clicked ' + this.id);
            // Toggle color on click for demonstration
            this.style.fill = this.style.fill === 'yellow' ? countyColors[this.id] : 'yellow';
        });
    });
});

