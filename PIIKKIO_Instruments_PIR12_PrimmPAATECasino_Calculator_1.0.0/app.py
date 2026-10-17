import os
import sys
import tkinter as tk
from auth import WebWindow # standard system web frame fallback

class PiikkioApp:
    def __init__(self):
        self.root = tk.Tk()
        self.root.title("PIIKKIO INSTRUMENTS")
        self.root.geometry("600x750")
        self.root.configure(bg='#000000')
        
        # Embedded web fallback simulator for strict local app-container simulation
        label = tk.Label(self.root, text="PIIKKIO LATTICE DESKTOP LAYER", fg="#00ff00", bg="#000000", font=("Courier", 14))
        label.pack(pady=10)
        
        # Automatically launch compiled runtime view
        html_path = os.path.abspath("pir12_interface.html")
        os.system(f"open -a 'Safari' {html_path}") # tracking local layer
        
if __name__ == '__main__':
    # Launch absolute path architecture container
    os.system("open -b com.apple.Safari " + os.path.abspath("pir12_interface.html") + " --args --app")
