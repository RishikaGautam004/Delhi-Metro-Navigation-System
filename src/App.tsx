import React, { useState } from 'react';
import { Train, Navigation, MapPin, AlertTriangle, Map } from 'lucide-react';
import { RouteCalculator } from './components/RouteCalculator';
import { DelaySimulation } from './components/DelaySimulation';
import { MetroMap } from './components/MetroMap';
import { StationList } from './components/StationList';

type TabType = 'route' | 'delay' | 'map' | 'stations';

function App() {
  const [activeTab, setActiveTab] = useState<TabType>('route');

  const tabs = [
    { id: 'route', label: 'Route Calculator', icon: Navigation },
    { id: 'delay', label: 'Delay Simulation', icon: AlertTriangle },
    { id: 'map', label: 'Metro Map', icon: Map },
    { id: 'stations', label: 'All Stations', icon: MapPin },
  ] as const;

  const renderContent = () => {
    switch (activeTab) {
      case 'route':
        return <RouteCalculator />;
      case 'delay':
        return <DelaySimulation />;
      case 'map':
        return <MetroMap />;
      case 'stations':
        return <StationList />;
      default:
        return <RouteCalculator />;
    }
  };

  return (
    <div className="min-h-screen bg-gradient-to-br from-blue-50 via-white to-purple-50">
      {/* Header */}
      <header className="bg-white shadow-sm border-b border-gray-200">
        <div className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8">
          <div className="flex items-center justify-between h-16">
            <div className="flex items-center">
              <div className="flex-shrink-0">
                <div className="flex items-center">
                  <div className="w-10 h-10 bg-gradient-to-r from-metro-blue to-metro-purple rounded-lg flex items-center justify-center">
                    <Train className="w-6 h-6 text-white" />
                  </div>
                  <div className="ml-3">
                    <h1 className="text-xl font-bold text-gray-900">Delhi Metro Navigator</h1>
                    <p className="text-sm text-gray-500">Smart Route Planning & Real-time Updates</p>
                  </div>
                </div>
              </div>
            </div>
            
            <div className="hidden md:block">
              <div className="flex items-center space-x-4">
                <div className="text-sm text-gray-500">
                  🚇 {new Date().toLocaleDateString('en-IN', { 
                    weekday: 'long', 
                    year: 'numeric', 
                    month: 'long', 
                    day: 'numeric' 
                  })}
                </div>
              </div>
            </div>
          </div>
        </div>
      </header>

      {/* Navigation Tabs */}
      <nav className="bg-white border-b border-gray-200 sticky top-0 z-40">
        <div className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8">
          <div className="flex space-x-8 overflow-x-auto">
            {tabs.map((tab) => {
              const Icon = tab.icon;
              return (
                <button
                  key={tab.id}
                  onClick={() => setActiveTab(tab.id)}
                  className={`flex items-center px-3 py-4 text-sm font-medium border-b-2 transition-colors duration-200 whitespace-nowrap ${
                    activeTab === tab.id
                      ? 'border-metro-blue text-metro-blue'
                      : 'border-transparent text-gray-500 hover:text-gray-700 hover:border-gray-300'
                  }`}
                >
                  <Icon className="w-4 h-4 mr-2" />
                  {tab.label}
                </button>
              );
            })}
          </div>
        </div>
      </nav>

      {/* Main Content */}
      <main className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8 py-8">
        {renderContent()}
      </main>

      {/* Footer */}
      <footer className="bg-gray-50 border-t border-gray-200 mt-16">
        <div className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8 py-8">
          <div className="text-center">
            <div className="flex items-center justify-center mb-4">
              <Train className="w-5 h-5 text-metro-blue mr-2" />
              <span className="text-gray-600 font-medium">Delhi Metro Navigator</span>
            </div>
            <p className="text-sm text-gray-500 mb-2">
              Intelligent route planning and real-time delay simulation for Delhi Metro
            </p>
            <p className="text-xs text-gray-400">
              Built with React, TypeScript, and modern web technologies
            </p>
          </div>
        </div>
      </footer>
    </div>
  );
}

export default App;