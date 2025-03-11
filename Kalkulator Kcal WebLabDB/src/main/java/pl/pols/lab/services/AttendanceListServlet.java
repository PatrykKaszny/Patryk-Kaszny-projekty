package pl.pols.lab.services;

import Model.Product;
import jakarta.servlet.ServletContext;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import pl.polsl.lab.model.DataSource;
import pl.polsl.lab.model.SingletonModel;

/**
 * Servlet responsible for managing the product list. It handles displaying products 
 * and deleting them based on their identifier.
 *
 * @version 1.1.0
 * @since 1.0
 * @author Patryk Kaszny
 */
@WebServlet("/attendanceList")
public class AttendanceListServlet extends HttpServlet {

    /**
     * Initializes the servlet. In this version, it does not contain any implementation.
     * It loads the products from the DataSource and adds them to the SingletonModel's product list.
     */
    @Override
    public void init() {
        var context = getServletContext();        
        DataSource dataSource = (DataSource) context.getAttribute("DataSource");  
        for(Product p : dataSource.getProductList()){     
            SingletonModel.getInstance().addToAllProducts(p.getName(), p.getProtein(), p.getCarb(), p.getFat());
        }    
    }

    /**
     * Processes the HTTP request and generates a response in the form of an HTML table displaying products.
     * Each product is shown with its name, protein, carbs, fat, weight, and calories.
     * Buttons are provided to delete or modify each product.
     * 
     * @param request the HTTP request object
     * @param response the HTTP response object
     * @throws ServletException if there is an issue with processing the request
     * @throws IOException if there is an issue with writing the response
     */
    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
        
        PrintWriter out = response.getWriter(); 
        int i = 0;
        // Iterates over all products and generates HTML table rows
        for(Product product : SingletonModel.getInstance().getAllProductList()) {            
            out.println("<tr>");
            out.println("<td>" + product.getName() + "</td>");
            out.println("<td>" + product.getProtein() + "</td>");
            out.println("<td>" + product.getCarb() + "</td>");
            out.println("<td>" + product.getFat() + "</td>");
            out.println("<td>" + product.getWeight() + "</td>");
            out.println("<td>" + product.getKcal() + "</td>");
            out.println("<td>");
            out.println("<button onclick=\"deleteProduct(" + i + ")\">Delete</button>");
            out.println("<button onclick=\"editProduct(" + i + ")\">Modify</button>");
            out.println("</td>");
            out.println("</tr>");
            i++;
        }        
    }

    /**
     * Handles the HTTP GET request. It checks for an optional product identifier parameter.
     * If the parameter is present, it deletes the corresponding product from the list.
     * If no product identifier is provided, it calls the processRequest method to display the list.
     * 
     * @param request the HTTP request object
     * @param response the HTTP response object
     * @throws ServletException if there is an issue with processing the request
     * @throws IOException if there is an issue with writing the response
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String productIdParam = request.getParameter("id");
        ServletContext context = request.getServletContext();
        DataSource dataSource = (DataSource) context.getAttribute("DataSource");

        // Check if a product ID is provided for deletion
        if (productIdParam != null) {
            try {
                int productId = Integer.parseInt(productIdParam);
                String Name = SingletonModel.getInstance().getAllProductList().get(productId).getName();
                boolean success = SingletonModel.getInstance().removeProductById(productId);
                dataSource.delete(Name);
                if (success) {
                    response.setStatus(HttpServletResponse.SC_OK);
                } else {
                    response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
                }
            } catch (NumberFormatException e) {
                // Handle invalid product ID
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid product identifier");
            }
        } else {
            processRequest(request, response); // If no ID, show the product list
        }
    }

    /**
     * Returns a short description of the servlet.
     * 
     * @return a string description of the servlet
     */
    @Override
    public String getServletInfo() {
        return "Servlet for managing the product list";
    }
}
