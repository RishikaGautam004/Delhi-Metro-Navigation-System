/** @type {import('tailwindcss').Config} */
export default {
  content: [
    "./index.html",
    "./src/**/*.{js,ts,jsx,tsx}",
  ],
  theme: {
    extend: {
      colors: {
        metro: {
          blue: '#0066CC',
          yellow: '#FFD320',
          red: '#E53E3E',
          green: '#38A169',
          orange: '#FF8C00',
          pink: '#ED64A6',
          purple: '#9F7AEA',
          gray: '#718096'
        }
      },
      animation: {
        'pulse-slow': 'pulse 3s cubic-bezier(0.4, 0, 0.6, 1) infinite',
        'bounce-slow': 'bounce 2s infinite',
      }
    },
  },
  plugins: [
    require('@tailwindcss/forms'),
  ],
}