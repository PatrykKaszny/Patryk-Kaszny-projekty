package pl.pols.lab.services;

import Model.Product;
import jakarta.servlet.ServletContext;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import pl.polsl.lab.model.DataSource;
import pl.polsl.lab.model.SingletonModel;

/**
 * Servlet for handling the calculator functionality. It processes the user's
 * input (name, protein, fat, carbohydrates), adds the product to the list, 
 * and redirects to the product list page.
 *
 * @version 1.1.0
 * @since 1.0
 * @author Patryk Kaszny
 */
public class CalculatorServlet extends HttpServlet {

    /**
     * Initializes the servlet. In this version, no specific initialization logic 
     * is provided.
     */
    @Override
    public void init() {
    }

    /**
     * Processes the HTTP request. Validates input parameters (name, protein, fat, 
     * carbohydrates) and adds the product to the list. If any parameters are missing 
     * or invalid, an error response is sent.
     * 
     * @param request the HTTP request object containing the user's input
     * @param response the HTTP response object used to send back a result
     * @throws ServletException if a servlet-specific error occurs during request processing
     * @throws IOException if an I/O error occurs while sending the response
     */
    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
        
        ServletContext context = request.getServletContext();
        DataSource dataSource = (DataSource) context.getAttribute("DataSource");
        
        // Retrieve the user input parameters
        String arg1 = request.getParameter("name");
        String arg2 = request.getParameter("protein");
        String arg3 = request.getParameter("fat");
        String arg4 = request.getParameter("carb");
        
        // Validate if any parameter is missing or empty
        if (arg1 == null || arg2 == null || arg3 == null || arg4 == null || 
            arg1.length() == 0 || arg2.length() == 0 || arg3.length() == 0 || arg4.length() == 0) {
            response.sendError(response.SC_BAD_REQUEST, "Missing parameters");
        } else {
            try {
                PrintWriter out = response.getWriter();
                out.println("<!DOCTYPE html>");
                out.println("<html>");
                out.println("<head>");
                out.println("<title>Calculator</title>");
                out.println("</head>");
                out.println("<body>");
                out.println("<h1>Calculator</h1>");
                out.println("</body>");
                out.println("</html>");
                
                // Add the new product to the SingletonModel's list of products
                SingletonModel.getInstance().addToAllProducts(arg1, Integer.parseInt(arg2), Integer.parseInt(arg3), Integer.parseInt(arg4));
                
                // Create a new Product object and persist it to the data source
                Product p = new Product(arg1, Integer.parseInt(arg2), Integer.parseInt(arg3), Integer.parseInt(arg4), 100);
                dataSource.persistObject(p);
                
                // Redirect to the product list page
                response.sendRedirect("attendanceList.html");
            } catch (Exception ex) {
                response.sendError(response.SC_BAD_REQUEST, "Numbers are required!");
            }
        }
    }

    /**
     * Handles the HTTP GET method. Calls the processRequest method to handle the GET request.
     * 
     * @param request the HTTP request object containing the user's input
     * @param response the HTTP response object used to send back a result
     * @throws ServletException if a servlet-specific error occurs during request processing
     * @throws IOException if an I/O error occurs while sending the response
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    /**
     * Handles the HTTP POST method. Calls the processRequest method to handle the POST request.
     * 
     * @param request the HTTP request object containing the user's input
     * @param response the HTTP response object used to send back a result
     * @throws ServletException if a servlet-specific error occurs during request processing
     * @throws IOException if an I/O error occurs while sending the response
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    /**
     * Returns a short description of the servlet.
     * 
     * @return a String containing the servlet description
     */
    @Override
    public String getServletInfo() {
        return "Servlet for adding products and redirecting to the product list page";
    }
}
