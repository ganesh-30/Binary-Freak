// Dummy items data (you can replace this with real inputs later)
const items = [
    { name: "Item 1", price: 45 },
    { name: "Item 2", price: 80 },
    { name: "Item 3", price: 65 },
    { name: "Item 4", price: 25 },
    { name: "Item 5", price: 90 },
];

// Store data in localStorage for billing page
localStorage.setItem("selectedItems", JSON.stringify(items));

window.onload = () => {
    const itemList = document.getElementById("item-list");
    const totalItems = document.getElementById("total-items");
    const totalAmount = document.getElementById("total-amount");

    let total = 0;

    items.forEach((item, index) => {
        const p = document.createElement("p");
        p.textContent = `${index + 1}. ${item.name} - ₹${item.price}`;
        itemList.appendChild(p);
        total += item.price;
    });

    totalItems.textContent = `No of Items - ${items.length}`;
    totalAmount.textContent = `Total - ₹ ${total}`;
};
