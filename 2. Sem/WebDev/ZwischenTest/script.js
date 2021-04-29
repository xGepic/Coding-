const container = document.getElementById('app');
const timezoneSelectUser = document.getElementById('timezone_user');
const timezoneSelectTarget = document.getElementById('timezone_target');
const dateSelect = document.getElementById('date');
const result = document.getElementById('result')

const fetchTimezones = async () => {
    const res = await fetch('api/timezones.php');
    const data = await res.json();

    return data;
}  

const populateSelect = async () => {
    const timezones = await fetchTimezones()
    
    timezones.map(timezone => {
        const node = document.createElement('option');
        node.setAttribute('value', timezone)
        node.innerHTML = timezone;

        timezoneSelectUser.appendChild(node);
        const copy = node.cloneNode(true)
        copy.innerHTML = timezone
        timezoneSelectTarget.appendChild(copy);
    })
}

const fetchResult = async (data) => {
    const res = await fetch('api/timezones.php', {
        method: 'POST',
        body: JSON.stringify(data)
    });
    const res_data = await res.json();

    result.innerHTML = res_data.timezone + ': ' + res_data.date
}


populateSelect()

const loadRes = async () => {await fetchResult({date: dateSelect.value, tzsource: timezoneSelectUser.value,tztarget: timezoneSelectTarget.value})}