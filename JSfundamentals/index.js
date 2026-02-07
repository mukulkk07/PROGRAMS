// 1. Import the package
const axios = require('axios');

async function getCatFact() {
  try {
    console.log("Fetching a cat fact...");

    // 2. Use the package to get data
    const response = await axios.get('https://catfact.ninja/fact');

    // 3. Print the result
    console.log("🐱 FACT:", response.data.fact);

  } catch (error) {
    console.error("Error fetching data:", error);
  }
}

getCatFact();