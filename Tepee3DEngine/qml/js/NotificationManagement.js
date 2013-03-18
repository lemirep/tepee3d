.pragma library

var messages;

function initialize()
{
    messages = new Array();
}

function addMessage(message)
{
    messages.push(message);
}

function getMessages()
{
    return messages;
}
